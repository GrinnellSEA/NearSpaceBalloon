const TESTING_MODE = true;
const POLLING_INTERVAL = 10; // seconds

let tempChart, presChart, altChart, battChart;
let map, path, marker;

async function main() {
    let response = await fetch("/rtty/all");
    if (!response.ok && !TESTING_MODE) return failConnection();
    if (!response.ok && TESTING_MODE) 
        response = await fetch("assets/test_data.txt");
    let text = await response.text();

    // show cards
    $(".page-content").hidden = false;
    $("#loading").hidden = true;
    showToast("Connection established.");

    let data = processText(text);

    updateBasicStats(data);

    tempChart = drawLineChart("#temp-graph", {
        time: data.time,
        data: data.temp,
        label: "Temperature (°F)",
    });
    presChart = drawLineChart("#pres-graph", {
        time: data.time,
        data: data.pres,
        label: "Pressure (mb)",
    });
    altChart = drawLineChart("#alt-graph", {
        time: data.time,
        data: data.alt,
        label: "Altitude (m)",
    });
    battChart = drawLineChart("#batt-graph", {
        time: data.time,
        data: data.batt,
        label: "Battery Voltage (V)",
        yTick: x => x.toFixed(1),
        yFormat: x => x.toFixed(1) + " V",
    });

    plotPath(data.coords);

    setInterval(update, POLLING_INTERVAL * 1000);
}

async function update() {
    let response = await fetch("/rtty/new");
    if (!response.ok && !TESTING_MODE) return failConnection();
    if (!response.ok && TESTING_MODE) 
        response = await fetch("assets/test_new_data.txt");
    let text = await response.text();

    let data = processText(text);
    if (data.time.length === 0) return;

    updateBasicStats(data);
    addData(tempChart, data.time, data.temp);
    addData(presChart, data.time, data.pres);
    addData(altChart, data.time, data.alt);
    addData(battChart, data.time, data.batt);
    addPathPoints(data.coords);
}

function processText(text) {
    let entries = text.split("\n");
    let length = entries.length;

    let data = {
        time: [],
        temp: [],
        pres: [],
        coords: [],
        alt: [],
        batt: [],
    };
    
    // iterate backwards through list
    for (let entry of entries) {
        let matches = entry.match(/GSEA~S(\d+)T(\d+)P(\d+)X(\d+)Y(\d+)A(\d+)B(\d+)~/);        
        // skip invalid entries
        if (matches === null) continue;

        let minutes = +matches[1] / 60;
        let kelvin = +matches[2] / 10;
        let pressure = +matches[3];
        let farenheit = (kelvin - 273.15) * 1.8 + 32;
        let longitude = -matches[4] / 10000;
        let latitude = +matches[5] / 10000;
        let altitude = +matches[6] / 10;
        let voltage = +matches[7] / 1000;

        data.time.push(minutes);
        data.temp.push(farenheit);
        data.pres.push(pressure);
        data.coords.push({
            lat: latitude,
            lng: longitude,
        });
        data.alt.push(altitude);
        data.batt.push(voltage);
    }

    return data;
}

function updateBasicStats(data) {
    $("#temp").innerText = Math.round(data.temp.last()) + " °F";
    $("#pres").innerText = data.pres.last() + " mb";
    $("#alt").innerText = data.alt.last() + " m";
    $("#time").innerText = "T+" + toTimeString(data.time.last());
    $("#batt").innerText = data.batt.last().toFixed(1);
}

function initMap() {
    let grinnell = {lat: 41.7491836, lng: -92.7213833};
    map = new google.maps.Map($("#map"), {
        zoom: 8,
        center: grinnell,
        mapTypeId: 'terrain',
        scrollwheel: false,
        streetViewControl: false,
    });
    setTimeout(() => google.maps.event.trigger(map, "resize"), 1000);
}

function plotPath(coords) {
    path = new google.maps.Polyline({
        path: coords,
        geodesic: true,
        strokeColor: '#c00000',
        strokeOpacity: 0.8,
        strokeWeight: 4,
    });

    path.setMap(map);

    var loc = coords.last();
    marker = new google.maps.Marker({
        position: loc,
        map,
    })

    setTimeout(() => map.panTo(loc), 1000);  
}

function addPathPoints(coords) {
    let pathObj = path.getPath();
    for (let pt of coords) {
        pathObj.push(new google.maps.LatLng(pt));
    }

    var loc = coords.last();
    marker.setPosition(loc);
    map.panTo(loc);  
}

function toTimeString(minutes) {
    let hours = Math.floor(minutes / 60);
    minutes = Math.floor(minutes) % 60;

    return ("0"+hours).slice(-2) + ":" + ("0"+minutes).slice(-2);
}

function failConnection() {
    setTimeout(() => {
        $("#loading").hidden = true;
        showToast("Failed to establish connection.");
    }, 2000);
}

function showToast(msg) {
    $("#toast").MaterialSnackbar.showSnackbar({
        message: msg,
        timeout: 4000,
    });
}

Array.prototype.last = function() {
    return this[this.length - 1];
};

