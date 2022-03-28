export default class Model{

    constructor(handleLoadData){
        this.handleLoadData = handleLoadData;
    }
    url = 'api.openweathermap.org/data/2.5/weather';

load(city) {
    if(!city == true)   {console.log('incorrect data!'); } 
        else {
        const ajax = new XMLHttpRequest();
        this.url = `https://api.openweathermap.org/data/2.5/weather?q=${city}&appid=b9e3f98af67596c1f3722b46793a5c7f`;
        ajax.addEventListener('load', () => {
            this.handleLoadData(JSON.parse(ajax.responseText));
        });
            ajax.open("GET", this.url, true);
            ajax.send();
        }   
    }
}
