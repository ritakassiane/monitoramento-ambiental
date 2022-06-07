<template>
    <div class="appliances">
        <div class="appliance">
            <input type="checkbox" name="a" id="a">
            <label for="a">
            <i class="l"></i>
            <strong>Luz</strong>
            <span data-o="medindo..." data-c="enviar"></span>
            <small></small>
            </label>
        </div>
        
        <div class="appliance">
            <input type="checkbox" name="a" id="b">
            <label for="b">
            <i class="r"></i>
            <strong>Temper</strong>
            <span data-o="medindo..." data-c="enviar"></span>
            <small></small>
            </label>
        </div>
        
        <div class="appliance">
            <input type="checkbox" name="a" id="c">
            <label for="c">
            <i class="a"></i>
            <strong>ATM</strong>
            <span data-o="medindo..." data-c="enviar"></span>
            <small></small>
            </label>
        </div>
        
        <div class="appliance">
            <input type="checkbox" name="a" id="d">
            <label for="d">
            <i class="f"></i>
            <strong>Umidade</strong>
            <span data-o="medindo..." data-c="enviar"></span>
            <small></small>
            </label>
        </div>
    </div>
</template>
<script>
export default {
    name:'Sensors'
}
</script>
<style scoped>
    .appliances {
    display: flex;
    flex-wrap: wrap;
    justify-content: space-between;
    width: 340px;
    margin: 30px auto;
    }
  
  .appliance {
    position: relative;
    height: 170px;
    width: 45%;
    margin: 10px 0;
  }
  .appliance span {
    position: relative;
  }
  .appliance span::before, .appliance span::after {
    text-transform: uppercase;
    font-size: 12px;
    position: absolute;
    left: 0;
  }
  .appliance span::before {
    content: attr(data-o);
    opacity: 0;
  }
  .appliance span::after {
    content: attr(data-c);
  }
  .appliance strong {
    margin: 70px 0 10px;
    display: block;
    font-size: 18px;
  }
  .appliance label {
    position: absolute;
    width: 74%;
    height: 71%;
    cursor: pointer;
    padding: 20px;
    box-shadow: 1px 0 10px 10px rgba(0, 0, 0, 0.03);
    border-radius: 30px;
  }
  .appliance label::before {
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
  .appliance label * {
    position: relative;
    transition: 200ms;
  }
  .appliance label small {
    position: absolute;
    width: 10px;
    height: 10px;
    background-color: #ff574e;
    border-radius: 10px;
    top: 30px;
    right: 20px;
    transition: 200ms;
  }
  .appliance label small::after, .appliance label small::before {
    content: "";
  }
  .appliance label .f {
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
  .appliance label .a {
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
  .appliance label .a::after, .appliance label .a::before {
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
  .appliance label .a::after {
    left: 14px;
  }
  .appliance label .a::before {
    left: 6px;
  }
  .appliance label .r {
    width: 23px;
    height: 9px;
    background-color: #3976f6;
    display: block;
    position: absolute;
    border-radius: 3px;
    top: 30px;
  }
  .appliance label .r::after, .appliance label .r::before {
    content: "";
    border-width: 2px;
    border-style: solid;
    border-color: rgba(57, 118, 246, 0.61) transparent transparent;
    border-radius: 50%;
    position: absolute;
    display: block;
  }
  .appliance label .r::after {
    width: 22px;
    height: 20px;
    top: -11px;
    left: -2px;
  }
  .appliance label .r::before {
    width: 16px;
    height: 20px;
    top: -6px;
    left: 1px;
  }
  .appliance label .l {
    width: 22px;
    height: 13px;
    background-color: #3976f6;
    display: block;
    position: absolute;
    border-radius: 22px 22px 0 0;
    top: 30px;
  }
  .appliance label .l::before {
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
  .appliance label .l::after {
    content: "";
    position: absolute;
    width: 10px;
    height: 4px;
    background: rgba(57, 118, 246, 0.61);
    border-radius: 0 0 9px 9px;
    top: 14px;
    left: 6px;
  }
  .appliance input {
    display: none;
  }
  .appliance input:checked + label::before {
    content: "";
    background: linear-gradient(to bottom, #59a2fb 0%, #3976f6 100%);
  }
  .appliance input:checked + label * {
    color: white;
  }
  .appliance input:checked + label i {
    background-color: white;
  }
  .appliance input:checked + label i::before, .appliance input:checked + label i::after {
    background-color: rgba(255, 255, 255, 0.61);
  }
  .appliance input:checked + label i.f {
    background-image: linear-gradient(0deg, rgba(89, 162, 251, 0.61) 2px, transparent 2px), linear-gradient(0deg, rgba(89, 162, 251, 0.61) 12px, transparent 0);
  }
  .appliance input:checked + label i.a {
    background-image: linear-gradient(0deg, rgba(89, 162, 251, 0.61) 2px, transparent 2px);
  }
  .appliance input:checked + label i.a::before, .appliance input:checked + label i.a::after {
    background-color: rgba(255, 255, 255, 0);
    border-color: transparent transparent rgba(255, 255, 255, 0.61);
  }
  .appliance input:checked + label i.r {
    background-color: white;
  }
  .appliance input:checked + label i.r::before, .appliance input:checked + label i.r::after {
    background-color: rgba(255, 255, 255, 0);
    border-color: rgba(255, 255, 255, 0.61) transparent transparent;
  }
  .appliance input:checked + label small {
    width: 30px;
    height: 15px;
    background-color: #3976f6;
  }
  .appliance input:checked + label small::before {
    width: 13px;
    height: 13px;
    background-color: white;
    display: block;
    border-radius: 13px;
    top: 1px;
    position: absolute;
  }
  .appliance input:checked + label span::before {
    opacity: 1;
  }
  .appliance input:checked + label span::after {
    opacity: 0;
  }
  

</style>