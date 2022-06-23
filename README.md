# 📌Monitoramento Ambiental - Sistemas Digitais
<p>
O investimento pesado que as empresas seguem fazendo na indústria 4.0 tem como resultado um mercado ainda mais competitivo. Em conjunto com  o advento de chips de computador e telecomunicações de alta largura de banda, agora temos bilhões de dispositivos conectados à Internet. Neste cenário, cada vez mais os governos locais e empresas têm usado a Internet das Coisas (IoT) para os mais diversos diversos usos.
	
Neste sentido, uma empresa contratou uma equipe de engenheiros da computação em formação, para desenvolver um protótipo de um sistema para monitoramento ambiental. O produto desenvolvido conta com um sistema comandado por Single Board Computer (SBC), a qual requisita as leituras realizadas pelos sensores e mostra os dados através de uma Interface Homem-Máquina. O produto ainda conta com uma interface remota que obtém os dados do SBC através de um protocolo de comunicação MQTT.
</p>

<h1>  👥Equipe: <br></h1>
<uL> 
	<li>Paulo Queiroz de Carvalho <br></li>
	<li>Rita Kassiane Santos  <br></li>
	<li>Rodrigo Damasceno Sampaio <br></li>
</ul>

<h1 align="center"> Sumário </h1>
<div id="sumario">
	<ul>
		<li><a href="#MQTT"> MQTT </a></li>
		<li><a href="#SBC"> SBC </a>
			<ul>
				<li><a href="#MLSEB">Leitura dos Eensores e Envio Para o Broker</a>
					<ul>
					   <li><a href="#DHT11">Sensor DHT11</a></li>
					   <li><a href="#Potenciomentro">Potenciômetro</a></li>
					   <li><a href="#Broker">Envio de dados para o Broker</a></li>
					</ul>
				</li>
				<li><a href="#IHM">Interface Homem-Máquina</a>
					<ul>
					    <li><a href="#Display">Display e Butões</a></li>
					    <li><a href="#Estados">Máquina de Estados da Interface</a></li>
					</ul>
				</li>
				<li><a href="#PDados">Permanencia de Dados</a></li>
			</ul>
		</li>
		<li><a href="#IRemota"> Interface Remota</a>
			<ul>
			    <li><a href="#Back">Backend</a>
					<ul>
					    <li><a href="#MQTTR">MQTT e Envio de Dados</a></li>
					    <li><a href="#API">Rest API</a></li>
					</ul>
			    </li>
			    <li><a href="#Front"> Frontend </a> </li>
		        </ul>
		</li>
		<li><a href="#MakeFille"> Como Executar </a> 
			<ul>
				<li><a href="#SRestAPI"> Subindo a Rest API </a> 
				<li><a href="#Vue"> Subindo a aplicação Vue.js </a> 
			</ul>
		</li>
		<li><a href="#MakeFille"> Conclusão </a> 
	</ul>	
</div>
<div id="recursos">
	<h1> Recursos </h1>
	<ul>
		<li>Kit de desenvolvimento Mercúrio IV</li>
		<li>FPGA Cyclone IV</li>
		<li>Raspberry Pi Zero<V/li>
	</ul>
	
</div>


	
</div>
<div id="raspberry">
	<h1> Configurando, enviado e recebendo dados na Raspberry Pi Zero </h1>
	
	
	
</div>
<div id="conclusao">
	<h1>Conclusão</h1>
	<p>
	Para atingir o objetivo solicitado neste problema foi necessário compreender conceitos da programação em Verilog e integrar código assembly e C, a fim de solidificar o entendimento dos conceitos básicos a cerca de protocolos de comunicação serial.
	Além disso, o problema solucionado cumpre <strong>todos</strong> os requisitos solicitados, e foi desenvolvido utilizando Raspberry Pi Zero e FPGA Cyclone IV, além de ter sido devidamente testado através da verificação do dado enviado e recebido utilizando o osciloscópio.
	</p>
</div>
