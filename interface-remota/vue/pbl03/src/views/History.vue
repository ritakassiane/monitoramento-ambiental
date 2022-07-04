<template>
    <div class="dashboard">
        <header>
          <div class="f fe">
            <div class="icon icon-w"></div>
            <div class="heading">
              <h5 class="date">6 Jun 2022</h5>
              <h2 class="title">PBL 3</h2>
            </div>
          </div>
          <!-- Valor principal -->
          <div class="actual-value">
            <div class="value">
              <strong>{{ history[0] }}°<sup>C</sup></strong>
            </div>
          </div>
          <!-- Histórico -->
          <div class="weather f">
            <div>
              <strong>{{ history[0] }}°<sup>C</sup></strong>
              <p>0</p>
            </div>
            <div>
              <strong>{{ history[1] }}</strong>
              <p>1</p>
            </div>
            <div>
              <strong>{{ history[2] }}</strong>
              <p>2</p>
            </div>
            <div>
              <strong>{{ history[3] }}</strong>
              <p>3</p>
            </div>
            <div>
              <strong>{{ history[4] }}</strong>
              <p>4</p>
            </div>
            <div>
              <strong>{{ history[5] }}</strong>
              <p>5</p>
            </div>
            <div>
              <strong>{{ history[6] }}</strong>
              <p>6</p>
            </div>
            <div>
              <strong>{{ history[7] }}</strong>
              <p>7</p>
            </div>
            <div>
              <strong>{{ history[8] }}</strong>
              <p>8</p>
            </div>
            <div>
              <strong>{{ history[9] }}</strong>
              <p>9</p>
            </div>
            <div>
              <strong>{{ history[10] }}</strong>
              <p>10</p>
            </div>
          </div>
        </header>
        <div class="category">
            <ul>
                <li><router-link to="/Time" custom ><a>Tempo</a></router-link></li>
                <li><router-link to="/Sensors" custom ><a class="active">Histórico</a></router-link></li>
            </ul>
        </div>
        <!-- Sensores -->
        <div class="sensors">
            <div class="sensor" v-on:click="change()">
                <input type="checkbox" name="a" id="a">
                <label for="a">
                <i class="l"></i>
                <strong>Luz</strong>
                <span data-o="medindo..." data-c="histórico"></span>
                <small></small>
                </label>
            </div>
            
            <div class="sensor">
                <input type="checkbox" name="a" id="b">
                <label for="b">
                <i class="r"></i>
                <strong>Temper</strong>
                <span data-o="medindo..." data-c="histórico"></span>
                <small></small>
                </label>
            </div>
            
            <div class="sensor">
                <input type="checkbox" name="a" id="c">
                <label for="c">
                <i class="a"></i>
                <strong>ATM</strong>
                <span data-o="medindo..." data-c="histórico"></span>
                <small></small>
                </label>
            </div>
            
            <div class="sensor">
                <input type="checkbox" name="a" id="d">
                <label for="d">
                <i class="f"></i>
                <strong>Umidade</strong>
                <span data-o="medindo..." data-c="histórico"></span>
                <small></small>
                </label>
            </div>
        </div>

    </div>
</template>
<script>
// import Sensors from '../components/Sensors.vue'
import api from '../services/api';

export default {
    name:'Main',
    components:{

    },
    data(){
      return{
        history: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        temperatura: [],
        umidade: [],
        pressao: [],
        luminosidade: []
      }
    },
    mounted(){
      api.get('/').then(response => {
        const array = response.data
        this.temperatura = array[0]
        this.umidade = array[1]
        this.luminosidade = array[2]
        this.pressao= array[3]
        console.log(this.temperatura)
      })
    },
    methods: {
        change: function(){
            var newList = []

            for (var i = 0; i < this.temperatura.length; i++){
                // document.write("<br><br>array index: " + i);
                var obj = this.temperatura[i];
                newList.push({temperatura: obj.temperatura, data: obj.data, horario: obj.horario})
                
                // this.history.push(obj.temperatura)
                // for (var key in obj){
                //     console.log(obj.temperatura)
                //     // console.log(obj[key])
                // }
                // alert(obj)
            }
            // this.history = newList;
            alert(JSON.stringify(newList))

        }
    }
}
</script>
<style  scoped>
    .value{
        font-size: 25px;
    }
  .dashboard {
    background-color: #f6f8fa;
    width: 420px;
    margin: auto;
    display: flex;
    flex-direction: column;
    justify-content: center;
    border-radius: 50px;
  }
  .actual-value {
    display: flex;
    align-items: center;
    justify-content: center;
    margin-top: -40px;
  }
  .value{
    position: relative;
    width: 150px;
    height: 150px;
    display: flex;
    align-items: center;
    justify-content: center;
    border-radius: 100%;
    box-shadow:  1px 4px 4px rgba(0, 0, 0, 0.25);;
    background-color: #fff;
    margin: 40px 0;
  }
  .value span {
    font-size: 80px;
    font-weight: 800;
    letter-spacing: -2px;
    position: relative;
    }
  .category {
    display: flex;
    justify-content: center;
  }
  .f p{
    font-size: 12px;
  }
  /* Sensores */
    .sensors {
    display: flex;
    flex-wrap: wrap;
    justify-content: space-between;
    width: 340px;
    margin: 30px auto;
    }
  
  .sensor {
    position: relative;
    height: 170px;
    width: 45%;
    margin: 10px 0;
  }
  .sensor span {
    position: relative;
  }
  .sensor span::before, .sensor span::after {
    text-transform: uppercase;
    font-size: 12px;
    position: absolute;
    left: 0;
  }
  .sensor span::before {
    content: attr(data-o);
    opacity: 0;
  }
  .sensor span::after {
    content: attr(data-c);
  }
  .sensor strong {
    margin: 70px 0 10px;
    display: block;
    font-size: 18px;
  }
  .sensor label {
    position: absolute;
    width: 74%;
    height: 71%;
    cursor: pointer;
    padding: 20px;
    box-shadow: 1px 0 10px 10px rgba(0, 0, 0, 0.03);
    border-radius: 30px;
  }
  .sensor label::before {
    border-radius: 30px;
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    z-index: 0;
    background-color: white;
    content: "";
  }
  .sensor label * {
    position: relative;
    transition: 200ms;
  }
  .sensor label small {
    position: absolute;
    width: 10px;
    height: 10px;
    background-color: #ff574e;
    border-radius: 10px;
    top: 30px;
    right: 20px;
    transition: 200ms;
  }
  .sensor label small::after, .sensor label small::before {
    content: "";
  }
  .sensor label .f {
    width: 16px;
    height: 22px;
    background-color: #3976f6;
    display: block;
    position: absolute;
    border-radius: 2px;
    top: 30px;
    background-image: linear-gradient(0deg, white 2px, transparent 2px), linear-gradient(0deg, white 12px, transparent 0);
    background-size: 17px 9px, 2px 15px;
    background-position: 0 0, 3px 0;
    background-repeat: no-repeat;
  }
  .sensor label .a {
    width: 23px;
    height: 10px;
    background-color: #3976f6;
    display: block;
    position: absolute;
    border-radius: 2px;
    top: 30px;
    background-image: linear-gradient(0deg, white 2px, transparent 2px);
    background-size: 17px 9px;
    background-position: 3px -2px;
    background-repeat: no-repeat;
  }
  .sensor label .a::after, .sensor label .a::before {
    content: "";
    position: absolute;
    width: 8px;
    height: 8px;
    border-width: 3px;
    border-style: solid;
    border-color: transparent transparent #3976f6;
    top: 10px;
    border-radius: 50%;
    transform: rotate(72deg);
    display: block;
  }
  .sensor label .a::after {
    left: 14px;
  }
  .sensor label .a::before {
    left: 6px;
  }
  .sensor label .r {
    width: 23px;
    height: 9px;
    background-color: #3976f6;
    display: block;
    position: absolute;
    border-radius: 3px;
    top: 30px;
  }
  .sensor label .r::after, .sensor label .r::before {
    content: "";
    border-width: 2px;
    border-style: solid;
    border-color: rgba(57, 118, 246, 0.61) transparent transparent;
    border-radius: 50%;
    position: absolute;
    display: block;
  }
  .sensor label .r::after {
    width: 22px;
    height: 20px;
    top: -11px;
    left: -2px;
  }
  .sensor label .r::before {
    width: 16px;
    height: 20px;
    top: -6px;
    left: 1px;
  }
  .sensor label .l {
    width: 22px;
    height: 13px;
    background-color: #3976f6;
    display: block;
    position: absolute;
    border-radius: 22px 22px 0 0;
    top: 30px;
  }
  .sensor label .l::before {
    content: "";
    width: 3px;
    height: 8px;
    background-color: rgba(57, 118, 246, 0.61);
    display: block;
    top: -8px;
    position: absolute;
    border-radius: 3px;
    left: 9px;
  }
  .sensor label .l::after {
    content: "";
    position: absolute;
    width: 10px;
    height: 4px;
    background: rgba(57, 118, 246, 0.61);
    border-radius: 0 0 9px 9px;
    top: 14px;
    left: 6px;
  }
  .sensor input {
    display: none;
  }
  .sensor input:checked + label::before {
    content: "";
    background: linear-gradient(to bottom, #59a2fb 0%, #3976f6 100%);
  }
  .sensor input:checked + label * {
    color: white;
  }
  .sensor input:checked + label i {
    background-color: white;
  }
  .sensor input:checked + label i::before, .sensor input:checked + label i::after {
    background-color: rgba(255, 255, 255, 0.61);
  }
  .sensor input:checked + label i.f {
    background-image: linear-gradient(0deg, rgba(89, 162, 251, 0.61) 2px, transparent 2px), linear-gradient(0deg, rgba(89, 162, 251, 0.61) 12px, transparent 0);
  }
  .sensor input:checked + label i.a {
    background-image: linear-gradient(0deg, rgba(89, 162, 251, 0.61) 2px, transparent 2px);
  }
  .sensor input:checked + label i.a::before, .sensor input:checked + label i.a::after {
    background-color: rgba(255, 255, 255, 0);
    border-color: transparent transparent rgba(255, 255, 255, 0.61);
  }
  .sensor input:checked + label i.r {
    background-color: white;
  }
  .sensor input:checked + label i.r::before, .sensor input:checked + label i.r::after {
    background-color: rgba(255, 255, 255, 0);
    border-color: rgba(255, 255, 255, 0.61) transparent transparent;
  }
  .sensor input:checked + label small {
    width: 30px;
    height: 15px;
    background-color: #3976f6;
  }
  .sensor input:checked + label small::before {
    width: 13px;
    height: 13px;
    background-color: white;
    display: block;
    border-radius: 13px;
    top: 1px;
    position: absolute;
  }
  .sensor input:checked + label span::before {
    opacity: 1;
  }
  .sensor input:checked + label span::after {
    opacity: 0;
  }
  

</style>