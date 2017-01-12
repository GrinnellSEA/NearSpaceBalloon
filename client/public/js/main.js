async function main() {
    let response = await fetch("/rtty/all");
    if (!response.ok) return;
    let text = await response.text();

    let entries = text.split("\n");
    let length = entries.length;
    // iterate backwards through list
    for (let i = length - 1; i >= 0; i--) {
        let entry = entries[i]; 

        let matches = entry.match(/GSEA \| Temperature (\d+) K, Pressure (\d+) mbar/);        
        // skip invalid entries
        if (matches === null) continue;

        let kelvin = +matches[1];
        let pressure = +matches[2];
        let farenheit = (kelvin - 273.15) * 1.8 + 32;

        updateBasicStats(farenheit, pressure);

        break;
    }
}

function updateBasicStats(temp, pres) {
    $("#temp").innerText = Math.round(temp) + " °F";
    $("#pres").innerText = pres + " mb";
}
