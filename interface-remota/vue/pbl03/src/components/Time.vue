<template>
    <form v-on:submit.prevent="submitForm">
        <div class="time">
            <div class="input">
                <input type="number" ref="myForm" placeholder="Tempo de leitura" id="time" min="1" max="50">
            </div>
            <div>
                <input type="submit" value="ENVIAR" id="enviar">
            </div>
        </div>
    </form> 
</template>
<script>
import api from '../services/api';

export default {
    name: 'SetTime',
    data(){
        return{
            form: {
                time: 1
            }
        }
    },
    methods:{
        submitForm(){
            console.log(this.$refs.myForm.value)
            this.form.time = this.$refs.myForm.value
            console.log(this.form)
            api.post('/send-time', this.form).then((res) => {
                console.log("Resposta da API")
                console.log(res)
            })
        }
    }
    
}
</script>
<style scoped>
    .time {
        display: flex;
        flex-wrap: wrap;
        justify-content: center;
        align-items: center;
        flex-direction: column;
        width: 100%;
        height: 150px;
        margin: 30px auto;
    }
    #time {
    font-size: 13px;
    min-width: 200px;
    min-height: 30px;
    padding:6px;
    margin-bottom: 20px;
    margin-top: -10px;
    border: none;
    box-shadow: 0px 4px 10px 3px rgba(0, 0, 0, 0.25);
    border-radius: 10px
    }

    input[type=number]::-webkit-inner-spin-button { 
    all: unset; 
    min-width: 30px;
    min-height: 45px;
    margin: 17px;
    padding: 0px;
    background-image: 
    linear-gradient(to top, transparent 0px, transparent 16px, #fff 16px, #fff 26px, transparent 26px, transparent 35px, #000 35px,#000 36px,transparent 36px, transparent 40px),
    linear-gradient(to right, transparent 0px, transparent 10px, #000 10px, #000 11px, transparent 11px, transparent 21px);
    transform: rotate(90deg) scale(0.8, 0.9);
    cursor:pointer;
    }

    #enviar {
        border:none;
        box-shadow:inset 0px 1px 0px 0px #54a3f7;
        background-color: #3976F6;
        border-radius: 20px;
        display:inline-block;
        cursor:pointer;
        color:#ffffff;
        font-size:13px;
        font-weight: 800;
        padding:6px 24px;
    }
</style>>

