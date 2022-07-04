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
          <div class="actual-value">
            <div class="value">
              <strong>{{ temperatura }}°<sup>C</sup></strong>
            </div>
          </div>
          <div class="weather f">
            <div>
              <strong>{{ temperatura }}°<sup>C</sup></strong>
              <p>Temperatura  </p>
            </div>
            <div>
              <strong>{{ umidade }}%</strong>
              <p>Umidade</p>
            </div>
            <div>
              <strong>{{ luminosidade }}</strong>
              <p>Luminosidade</p>
            </div>
            <div>
              <strong>{{ luminosidade }}</strong>
              <p>Pressão</p>
            </div>
          </div>
        </header>
        <div class="category">
            <!-- <ul>
                <li><router-link to="/Time" custom ><a class="active">Tempo</a></router-link></li>
                <li><router-link to="/Sensors" custom ><a>Histórico</a></router-link></li>
            </ul> -->
        </div>

      <Time />
    </div>
</template>
<script>
import Time from './Time.vue'
import api from '../services/api';

export default {
    name:'Main',
    components:{
        Time
    },
    data(){
      return{
        temperatura: "-",
        umidade: "-",
        luminosidade: "-"
      }
    },
    mounted(){
      api.get('/temperatura', {
   headers: {
          // remove headers
        }
      }).then(res => {
        console.log(res);
      }).catch(err => {
        console.log(err.response);
      }).then(response => {
        console.log("Entrou aqui")
        const array = response.data
        var lastElement = (array.length)-1
        this.temperatura = array[lastElement].temperatura
        console.log(this.temperatura)
        console.log(lastElement)
      }),
      api.get('/umidade', {
   headers: {
          // remove headers
        }
      }).then(res => {
        console.log(res);
      }).catch(err => {
        console.log(err.response);
      }).then(response_umid => {
        const umid = response_umid.data
        const lastElement = (umid.length)-1
        this.umidade = umid[lastElement].umidade
        console.log(this.umidade)
      }),
      api.get('/luminosidade', {
   headers: {
          // remove headers
        }
      }).then(res => {
        console.log(res);
      }).catch(err => {
        console.log(err.response);
      }).then(response => {
        const lumin = response.data   
        const lastElement = (lumin.length)-1
        this.luminosidade = lumin[lastElement].luminosidade
        console.log(this.luminosidade)
      })
    }
}
</script>
<style  scoped>
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

</style>