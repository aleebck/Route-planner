const fromCity = document.querySelector('#from-city');
const toCity = document.querySelector('#to-city');
const findRouteButton = document.querySelector('.find-route-button');
const routeFound = document.querySelector('.route-found');
const allRoads = document.querySelector('.all-roads');

const map = L.map('map').setView([31.0, -99.0], 6);
L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; OpenStreetMap contributors'
}).addTo(map);

const austinMarker = L.marker([30.2672, -97.7431]);
austinMarker.addTo(map);
austinMarker.bindPopup('Austin');


fetch('http://localhost:8080/locations')
    .then(response=> response.json())
    .then(locations=> {
        locations.forEach(city => {

            const fromOption = document.createElement('option');
            fromOption.value = city;
            fromOption.textContent = city;
            fromCity.appendChild(fromOption);

            const toOption = document.createElement('option');
            toOption.value = city;
            toOption.textContent = city;
            toCity.appendChild(toOption);
        });
    });


findRouteButton.addEventListener('click', function() {
    const start = fromCity.value;
    const destination = toCity.value;

    fetch(`http://localhost:8080/route?start=${encodeURIComponent(start)}&destination=${encodeURIComponent(destination)}`)
        .then(response => response.json())
        .then(result => {
            routeFound.textContent = `Total Distance: ${result.distance} miles`;
            allRoads.textContent = result.path.join(' → ');
        });
});

