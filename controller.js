import Model from './model.js';
import View from './view.js';

export default class Controller{
    constructor(){
        this.view = new View(this.handleInputWeather);
        this.model = new Model(this.handleLoadData);
    }
    
    handleInputWeather = () => {
        this.model.load(this.view.get_city());
    }

    handleLoadData = (data) => {
        this.view.renderWeather(data);
    } 
}
