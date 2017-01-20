const TESTING_MODE = true;
const POLLING_INTERVAL = 20; // seconds

let tempChart, presChart, altChart;

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

    setInterval(update, POLLING_INTERVAL * 1000);
}

async function update() {
    let response = await fetch("/rtty/new");
    if (!response.ok && !TESTING_MODE) return failConnection();
    if (!response.ok && TESTING_MODE) 
        response = await fetch("assets/test_new_data.txt");
    let text = await response.text();

    let data = processText(text);

    updateBasicStats(data);
    addData(tempChart, data.time, data.temp);
    addData(presChart, data.time, data.pres);
    addData(altChart, data.time, data.alt);
}

function processText(text) {
    let entries = text.split("\n");
    let length = entries.length;

    let data = {
        time: [],
        temp: [],
        pres: [],
        lat: [],
        lon: [],
        alt: [],
    };
    
    // iterate backwards through list
    for (let entry of entries) {
        let matches = entry.match(/GSEA~S (\d+)~T (\d+)~P (\d+)~X (\d+)~Y (\d+)~A (\d+)~/);        
        // skip invalid entries
        if (matches === null) continue;

        let minutes = +matches[1] / 60;
        let kelvin = +matches[2] / 10;
        let pressure = +matches[3];
        let farenheit = (kelvin - 273.15) * 1.8 + 32;
        let longitude = +matches[4] / 10000;
        let latitude = +matches[5] / 10000;
        let altitude = +matches[6] / 10;

        data.time.push(minutes);
        data.temp.push(farenheit);
        data.pres.push(pressure);
        data.lon.push(longitude);
        data.lat.push(latitude);
        data.alt.push(altitude);
    }

    return data;
}

function updateBasicStats(data) {
    $("#temp").innerText = Math.round(data.temp.last()) + " °F";
    $("#pres").innerText = data.pres.last() + " mb";
    $("#alt").innerText = data.alt.last() + " m";
    $("#time").innerText = "T+" + toTimeString(data.time.last());
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
