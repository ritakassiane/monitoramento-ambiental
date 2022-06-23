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
	<ol>
		<li><a href="#MQTT"> MQTT </a></li>
		<li><a href="#SBC"> SBC </a>
			<ol>
				<li><a href="#MLSEB">Leitura dos Eensores e Envio Para o Broker</a>
					<ol>
					   <li><a href="#DHT11">Sensor DHT11</a></li>
					   <li><a href="#Potenciomentro">Potenciômetro</a></li>
					   <li><a href="#Broker">Envio de dados para o Broker</a></li>
					</ol>
				</li>
				<li><a href="#IHM">Interface Homem-Máquina</a>
					<ol>
					    <li><a href="#Display">Display e Butões</a></li>
					    <li><a href="#Estados">Máquina de Estados da Interface</a></li>
					</ol>
				</li>
				<li><a href="#PDados">Permanencia de Dados</a></li>
			</ol>
		</li>
		<li><a href="#IRemota"> Interface Remota</a>
			<ol>
			    <li><a href="#Back">Backend</a>
					<ol>
					    <li><a href="#MQTTR">MQTT e Envio de Dados</a></li>
					    <li><a href="#API">Rest API</a></li>
					</ol>
			    </li>
			    <li><a href="#Front"> Frontend </a> </li>
		        </ol>
		</li>
		<li><a href="#MakeFille"> Como Executar </a> 
			<ol>
				<li><a href="#SRestAPI"> Subindo a Rest API </a> 
				<li><a href="#Vue"> Subindo a aplicação Vue.js </a> 
			</ol>
		</li>
		<li><a href="#conclusao"> Conclusão </a> 
	</ol>	
<div id="MQTT">
	<h1>  MQTT </h1>
	<p>O Message Queue Telemetry Transport (MQTT) é um protocolo de comunicação entre máquinas (Machine to Machine - M2M) utilizado neste sistema para os envios de mensagens e comandos do Client local e o Client remoto, por intermédio do nosso servidor broker MQTT, sendo o mosquitto este utilizado.</p>
	<p>O nosso Client local foi desenvolvido em C e conta com a utilização da biblioteca <a href="https://mosquitto.org/api/files/mosquitto-h.html">mosquitto.h.</a> Através do  “Publish” deste Client é que os dados lidos através dos sensores, o tempo de medição destes e data das medições,  são publicados em tópicos do broker para que qualquer Client “Subscriber” possa ter acesso. Além disso, esse Client está inscrito no tópico de tempo de medição, para que quando esta configuração for alterada remotamente, o sistema entenda e modifique o tempo de leitura dos sensores localmente.</p>
	<p>Por sua vez o Client remoto está inscrito em todos os tópicos do nosso broker, com a finalidade de que seja possível mostrar em tempo real para o usuário as novas medições feitas. O Client remoto conta com somente um “Publish”, o qual funciona de modo que, ao ocorrer uma alteração do tempo de medição, esse novo dado seja enviado para o broker a fim de que o SBC possa sincronizar e efetivar as novas leituras dos sensores no tempo estipulado. O seu desenvolvimento foi feito utilizando a linguagem python e com auxílio da biblioteca <a href="https://www.eclipse.org/paho/index.php?page=clients/python/index.php">paho MQTT.</a></p>	
</div>
	
<div id="MQTTR">
	<h1>MQTT e Envio de Dados</h1>
	<pr>Como dito no tópico de <a href="#MQTT">MQTT</a>, a interface remota está inscrita no tópico que contém uma payload com uma string no modelo de “00/00/0000;00:00:00;000;000;000;000”, sendo ele interpretado da seguinte forma:<pr> <br></br>
<ol>
	<li>Os 10 primeiros caracteres (incluindo as “/” ) são referentes a data da medição realizada.</li>
	<li>Os 8 caracteres em sequência (incluindo os “:”) são referentes ao horário em que a medição foi realizada.</li>
	<li>Os próximos 4 agrupamentos de 3 caracteres separados por “;” são equivalentes respectivamente a umidade, temperatura, pressão atmosférica e luminosidade 	     </li>
</ol>	
<pr>Esse dado após ser recebido pelo Client, ele é tratado e separado de forma a ser convertido em um JSON, o qual servirá de base para a nossa API.</pr>
</div>
	
<div id="conclusao">
	<h1>Conclusão</h1>
	<p>
	Para atingir o objetivo solicitado neste problema foi necessário compreender conceitos da programação em Verilog e integrar código assembly e C, a fim de solidificar o entendimento dos conceitos básicos a cerca de protocolos de comunicação serial.
	Além disso, o problema solucionado cumpre <strong>todos</strong> os requisitos solicitados, e foi desenvolvido utilizando Raspberry Pi Zero e FPGA Cyclone IV, além de ter sido devidamente testado através da verificação do dado enviado e recebido utilizando o osciloscópio.
	</p>
</div>
