const fromCity = document.querySelector('#from-city');
const toCity = document.querySelector('#to-city');

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

const findRouteButton = document.querySelector('.find-route-button');

findRouteButton.addEventListener('click', function() {
    const start = fromCity.value;
    const destination = toCity.value;

    fetch(`http://localhost:8080/route?start=${encodeURIComponent(start)}&destination=${encodeURIComponent(destination)}`)
        .then(response => response.json())
        .then(result => {
            console.log(result);
        });
});

