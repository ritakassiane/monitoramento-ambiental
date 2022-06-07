<template>
    <div class="category">
        <ul>
            <li><a href="#!" class="active">Tempo</a></li>
            <li><a href="#!">Histórico</a></li>
            <!-- <li><a href="#!">Lorem</a></li>
            <li><a href="#!">Lorem</a></li> -->
        </ul>
    </div>
</template>
<script>
export default {
    name:'Category'
}
</script>
<style scoped>
.category {
overflow: hidden;
margin-top: 30px;
}
.category ul {
display: flex;
}
.category li + li {
margin-left: 40px;
}
.category a {
font-size: 17px;
font-weight: 600;
color: #858d9f;
white-space: nowrap;
}
.category a:hover, .category a.active {
color: #444;
}
.category a.active {
position: relative;
}
.category a.active::before {
content: "";
width: 6px;
height: 6px;
border-radius: 6px;
background-color: #444;
position: absolute;
left: 0;
right: 0;
margin: auto;
bottom: -15px;
}
</style>