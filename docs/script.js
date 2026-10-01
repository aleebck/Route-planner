const fromCity = document.querySelector('#from-city');
const toCity = document.querySelector('#to-city');
const findRouteButton = document.querySelector('.find-route-button');
const routeFound = document.querySelector('.route-found');
const allRoads = document.querySelector('.all-roads');

let routeLine;
let routeMarkers = [];

const map = L.map('map').setView([31.0, -99.0], 6);
L.tileLayer(
    'https://tile.openstreetmap.org/{z}/{x}/{y}.png',
    {
        maxZoom: 19,
        attribution: '&copy; OpenStreetMap contributors'
    }
).addTo(map);

fetch('https://route-planner-i48u.onrender.com/locations')
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

    if (start === '' || destination === '') {
        routeFound.textContent = 'Please select both cities.';
        allRoads.textContent = '';
        return;
    }

    if (start === destination) {
        routeFound.textContent = 'Please select two different cities.';
        allRoads.textContent = '';
        return;
    }

    fetch(`https://route-planner-i48u.onrender.com/route?start=${encodeURIComponent(start)}&destination=${encodeURIComponent(destination)}`)
        .then(response => response.json())
        .then(result => {
            if (!result.path || result.path.length === 0) {
                routeFound.textContent = 'No route found between these cities.';
                allRoads.innerHTML = '';

                if (routeLine) {
                    map.removeLayer(routeLine);
                    routeLine = null;
                }

                routeMarkers.forEach(marker => {
                    map.removeLayer(marker);
                });

                routeMarkers = [];

                return;
            }

            routeFound.textContent = `Total Distance: ${result.distance} miles`;
            allRoads.innerHTML = '';
            allRoads.style.display = 'block';

            result.path.forEach((city, index) => {
                const cityItem = document.createElement('div');
                cityItem.classList.add('route-city');

                cityItem.innerHTML = `
                    <div class="route-number">${index + 1}</div>
                    <div class="route-city-name">${city}</div>
                `;

                allRoads.appendChild(cityItem);
            });

            const routeCoordinates = result.path.map(city => {
                return cityCoordinates[city];
            });

            const osrmCoordinates = routeCoordinates.map(coord => {
                return `${coord[1]},${coord[0]}`;
            });
            
            const coordinateString = osrmCoordinates.join(';');

            fetch(`https://router.project-osrm.org/route/v1/driving/${coordinateString}?overview=full&geometries=geojson`)
            .then(response => response.json())
            .then(data => {
                const roadCoordinates = data.routes[0].geometry.coordinates.map(coord => {
                    return [coord[1], coord[0]];
            });
            if (routeLine) {
                map.removeLayer(routeLine);
            }

            routeLine = L.polyline(roadCoordinates, {
                color: '#2f80ff',
                weight: 5,
                opacity: 1
            }).addTo(map);

            routeMarkers.forEach(marker => {
                map.removeLayer(marker);
            });

            routeMarkers = [];

            result.path.forEach(city => {
                const marker = L.marker(cityCoordinates[city])
                .addTo(map)
                .bindPopup(city);

                routeMarkers.push(marker);
            })

            map.fitBounds(routeLine.getBounds());
        });
    })
    .catch(error => {
        console.error(error);
        routeFound.textContent = 'Unable to find route.';
        allRoads.textContent = '';
    });
});

