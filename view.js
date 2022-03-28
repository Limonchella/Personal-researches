export default class View{
    
    constructor(handleInputWeather){
        this.weather_result = document.querySelector('.info');
        document.querySelector('.btn-weather').addEventListener('click', handleInputWeather);
       
    }
    get_city(){    
    const city = document.getElementById("city_1").value;
    if(!city) return 0;
    return city;
    }
    
    renderWeather(weather){
        const { 
            main : { temp, temp_min, temp_max }, 
            //wind : { speed },
            name,
            coord : { lon, lat },
            weather: [
              {
              id,
              main,
              description,
              icon
              }
            ]
            } = weather;
        console.log(temp);
        console.log(temp_min);
        console.log(temp_max);
        const userHTML = `
        <div class="card">
        <div class="card-header">
          Name of city - ${name}  
        </div>
        <div class="card-body">
          <blockquote class="blockquote mb-0 ">
          <img src="http://openweathermap.org/img/w/${icon}.png"/>The weather is ${description} now.
         
            <p>Temprature ${(temp-273.15).toFixed(2)}, min ${(temp_min-273.15).toFixed(2)}, max ${(temp_max-273.15).toFixed(2)} </p>
            <footer class="blockquote-footer">Location <cite title="Координаты">${lon}, ${lat}</cite></footer>
          </blockquote>
        </div>
      </div>`;
    
      this.weather_result.innerHTML = userHTML;
    } 
}