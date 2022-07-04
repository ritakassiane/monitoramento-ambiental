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

<div id="SBC">
	<h1>SBC</h1>
	<p>A SBC utilizada para esse projeto foi uma (rasp) que executa apenas um programa, feito em C, com três finalidades: Ler continuamente os sensores monitorados, controlar uma interface homem máquina localmente utilizando de um display LCD e botões e enviar e receber dados através da comunicação MQTT. Todas as funcionalidades são feitas em um mesmo processo, contudo em threads diferentes, uma para os sensores e envio de dados para o broker, outra para a interface local homem máquina e uma terceira para receber um dado publicado no broker. A seguir, um detalhamento para cada uma dessas threads.</p>
</div>

<div id="MLSEB">
	<h1>Leitura dos sensores e envio de dados para o broker</h1>
	<p>A leitura dos sensores é feita continuamente de tempo em tempo, esse que inicia com 6s e pode ser alterado, e nos retorna umidade, temperatura, pressão e luminosidade onde a umidade e temperatura são medidos por um sensor DHT11 e a pressão junto com a luminosidade são simulados por dois potenciômetros a fim de gerar um sinal analógico para a SBC. Após a leitura dos sensores é verificado os dados e então são salvos e enviados para o broker. Nos próximos tópicos são detalhados como foi feita a leitura dos sensores e o envio dos dados lidos para o broker.</p>
</div>

<div id"DHT11">
	<h1>Sensor DHT11</h1>
	<p>O sensor DHT11 é um sensor assíncrono onde a diferença de 0 e 1 no dado enviado é obtido pelo tempo que o sinal fica em alta, 0 caso o sinal fique em alta por 28ns e 1 caso o sinal fique em alta por 70ns. Para a sua medição foi utilizado como base um código do <a href="https://github.com/Microcontrolandos/DHT11">GitHub.</a> o qual recebe dois ponteiros para arrays de caracteres, para cada caractere representa um byte, adicionando neles os valores lido e retornando se a leitura foi feita com sucesso, caso contrário informando o erro gerado.</p>
<p>Com o intuito de se encaixar com o nosso programa, o código base sofreu algumas alterações simples para se encaixar na biblioteca wiringPi, a primeira foi utilizar as funções da própria biblioteca para o gerenciamento das GPIOs e a segunda foi a adição de um novo parâmetro na chamada da função que indica em qual GPIO está conectado o sensor.</p>
<p>No código principal a leitura da umidade e temperatura é feita pela pela função readDHT11() que lê o sensor e escreve a parte inteira dos valores lidos em uma variável global newMeasure, caso o sensor dê algum erro o valor escrito será -1 independente do erro dado.</p>
</div>

<div id="Potenciomentro">
	<h1>Potenciômetros</h1>
	<p>Os potenciómetros foram utilizados como simuladores de sensores de pressão e luminosidade já que os mesmo normalmente são sensores analogicos. A SBC utilizada não contém uma porta analógica já implementada, por conta disso é utilizado um componente externo que faz essa leitura, no caso um ADS1115. Para a leitura desse componente é usado como base um código do <a href="https://github.com/giobauermeister/ads1115-linux-rpi">GitHub.</a>  que entende a conversão analogica I2C e retorna o valor dado. Para esse código, diferente do da leitura do DHT11, não foram feitas alterações significativas para a sua utilização.</p>
</div>
	
<div id="Broker">
	<h1>Envio dos dados para o broker</h1>
	<p>Após a leitura dos dados dos sensores, é feita uma análise se os dados lidos são válidos, no nosso caso se a umidade ou a temperatura são diferentes de -1, caso sejam, os dados são salvos no vetor global que guarda o histórico, caso o dado lido não seja válido, será ignorado a medição e repetirá o último dado lido como se fosse o dado atual.</p>
<p>Com os dados salvos no histórico local é então publicado no tópico “measuresSBC” as medidas calculadas junto com a data e hora da medição seguindo o padrão “data;hora;umidade;temperatura;pressão;luminosidade” de tal forma que os valores sempre estejam escritos com 3 casas decimais (ex: 22/06/2022;22:47:30;022;063;125;328). Por fim a thread volta a esperar o tempo determinado para a próxima medição.</p>
</div>
	
<div id="IHM">
	<h1>Interface Homem-Máquina</h1>
	<p>A interface Homem-Máquina da SBC, também chamada de interface local, é feita com 3 botões como input e o display LCD como output e a lógica do menu foi construída utilizando a filosofia de máquinas de estados. A seguir é detalhado mais as duas partes da interface local.</p>
</div>

<div id="Display">
	<h1>Display e botões </h1>
	<p>O display LCD utilizado contém 2 linhas de 16 caracteres cada de tal forma que, em nossa interface, a primeira linha é destinada para demonstrar dados, local do menu ou perguntas para o usuário e a linha de baixo e destinada para as opções que usuário pode selecionar no momento utilizando os botões podendo passar o menu para direita ou esquerda, selecionar algo, voltar para o menu entre outras.</p>
</div>
	
<div id="Estados">
	<h1>Máquina de Estados da Interface</h1>
	<p>A interface local é construída usando a filosofia de máquinas de estados onde o programa entende de forma diferente os inputs dependendo de onde o usuário se encontra na mesma. Os estados presentes são o Start, Menu, Historic, Editor e Exit seguindo a lógica descrita no diagrama abaixo.</p>
<p><h1>(Foto do diagrama)</h1></p>
<p>No estado de Start é demonstrado que o programa está executando. Nele todas as threads e valores iniciais são criados, o histórico salvo em arquivo é lido e uma mensagem simbólica e escrita no display LCD, mudando de estado para Menu assim que qualquer botão é pressionado. O estado Menu é o principal estado da interface, pois dele podemos ir para quaisquer outros 3 estados e os mesmo sempre voltam para esse. Neste estado podemos selecionar ver os dados medidos junto com o histórico, indo para o estado Historic, alterar o tempo de medição, indo para Edit, ou finalizar o processo, indo para Exit.</p>
 <p>Dependendo da opção escolhida, o estado Historic mostra as dez últimas medidas feitas do dado escolhido mostrando sequencialmente o momento que foi lido do sensor e depois o dado lido. O estado Edit é onde é possível alterar o tempo de medição, não podendo ser menor que três segundos, de tal forma que quando volta para o estado de Menu o novo tempo é enviado para o broker no tópico de “timeMeasure”.</p>
<p>Quando o programa chega no estado de Exit, pergunta para o usuário se tem a real intenção de finalizar o programa, caso afirmativo, ele salva os dados medidos no arquivo de histórico do mesmo formato que enviado para o tópico “measures“ do broker, finaliza qualquer coneção com o mesmo e finaliza todas as threads.</p>
</div>

<div id="PDados">
	<h1>Recebimento de uma publicação no Broker</h1>
	<p>O tempo de medição que a thread de leitura dos sensores utiliza pode ser alterada por qualquer interface homem-máquina, independente de ser local ou externa. Para isso o tempo de medição é um tópico do broker que qualquer interface pode publicar e que a sbc se inscreve tendo essa thread para “escutar” continuamente o broker. Assim que uma interface publicar um valor o programa atualiza uma variável global sTime, fazendo com que a próxima espera para uma nova leitura já seja com o novo valor.</p>
</div>
	
<div id="IRemota">
	<h1>Interface Remota</h1>
	<p>Para ser possível acessar as medições remotamente, foi desenvolvido uma interface web  capaz de coletar os dados e configurar o tempo da estação de medição. Esse módulo é subdividido em dois, os quais são: Backend e Frontend</p>
</div>
	
	
<div id="MQTTR">
	<h1>Backend: MQTT e Envio de Dados</h1>
	<pr>Como dito no tópico de <a href="#MQTT">MQTT</a>, a interface remota está inscrita no tópico que contém uma payload com uma string no modelo de “00/00/0000;00:00:00;000;000;000;000”, sendo ele interpretado da seguinte forma:<pr> <br></br>
<ol>
	<li>Os 10 primeiros caracteres (incluindo as “/” ) são referentes a data da medição realizada.</li>
	<li>Os 8 caracteres em sequência (incluindo os “:”) são referentes ao horário em que a medição foi realizada.</li>
	<li>Os próximos 4 agrupamentos de 3 caracteres separados por “;” são equivalentes respectivamente a umidade, temperatura, pressão atmosférica e luminosidade 	     </li>
</ol>	
<pr>Esse dado após ser recebido pelo Client, ele é tratado e separado de forma a ser convertido em um JSON, o qual servirá de base para a nossa API.</pr>
</div>
	
<div id="API">
	<h1>Backend: Rest API </h1>
	<p>Um programa desenvolvido utilizando Python, o qual consiste na implementação de uma API capaz de capturar as requisições enviadas pelo front-end, e se conectar com o broker para devolver dados acerca dos sensores, os quais através de um endpoint podem ser acessados por aplicações externas. 
A Rest API desenvolvida possui os seguintes endpoints:</p>
<p>/send-data [POST]: Esse endpoint é responsável por receber requisições do tipo POST de dados no formato JSON acerca das medições do sensor. O padrão de request pode ser representado por:</p>
{
    "data": 07/09/2000,
     "horario": 14:30,
     "temperatura": 25,
     "umidade": 38,
      "pressao": 1
      "luminosidade": 27
}</p>
<p>/  [GET] : Retorna uma lista que possui uma lista para cada sensor. Cada posição desta equivale a um valor medido e enviado para o endpoint POST descrito no tópico anterior. O template padrão pode ser representado por:
[
{
    "data": 07/09/2000,
     "horario": 14:30,
     "temperatura": 25,
     "umidade": 38,
      "pressao": 1
      "luminosidade": 27
},
{
    "data": 07/09/2000,
     "horario": 14:30,
     "temperatura": 25,
     "umidade": 38,
      "pressao": 1
      "luminosidade": 27
}
]</p>

<p>/temperatura [GET]: Endpoint que aceita requisições GET para que seja possível consumir dados acerca do sensor que mede temperatura.
		[{
    "data": 07/09/2000,
     "horario": 14:30,
  		    “temperatura”: 22
}]</p>
<p>/umidade [GET]:  Endpoint que aceita requisições GET para que seja possível consumir dados acerca do sensor que mede umidade.
		[{
    "data": 07/09/2000,
     "horario": 14:30,
  		    “umidade”: 59
}]</p>
<p>luminosidade [GET]:  Endpoint que aceita requisições GET para que seja possível consumir dados acerca do sensor que mede luminosidade.
		[{
    "data": 07/09/2000,
     "horário": 14:30,
  		    “luminosidade”: 60
}]</p>
<p>/pressao [GET]:  Endpoint que aceita requisições GET para que seja possível consumir dados acerca do sensor que mede pressão.
		[{
    "data": 07/09/2000,
     "horario": 14:30,
  		    “pressao”: 1
}]</p>

	
</div>
	
<div id="Front">
	<h1>Frontend</h1>
	<p>Uma aplicação que utiliza o framework Vue.JS para implementar a interface do usuário previamente definida [imagem do UI] a qual é capaz de enviar requisições e exibir dados consumidos de uma API que se comunica com o broker. Para realizar a comunicação com a API utilizou-se o cliente HTTP Axios.</p>
</div>
	
<div id="MakeFille">
	<h1>Como executar</h1>
	<p>Para executar localmente, configure e execute o broker Mosquitto. Posteriormente, abra um terminal no diretório /SBC e para inicializar a interface local e leitura dos sensores, execute o comando: <h5 align="center">make all</h5></p>
</div>
	
<div id="SRestAPI">
	<h1>Subindo a REST API</h1>
	<p>
Utilizando o gerenciador de pacotes pip, execute o seguinte comando para instalar as dependências: 
	<h5 align="center">pip install -r requirements.txt</h5>
Posteriormente, execute o arquivo api.py localizado no diretório /MQTT_Remoto/api.py</p>
</div>
	
<div id="Subindo a aplicação Vue.js">
	<h1>Interface Remota</h1>
	<p>Abra um terminal dentro do diretório principal do projeto Vue, e utilizando o gerenciador de pacotes npm, execute o seguinte comando para instalar as dependências e rodar localmente, respectivamente:
	<h5 align="center">npm install</h5>
	<h5 align="center">npm run serve</h5>
	</p>
</div>
		
<div id="conclusao">
	<h1>Conclusão</h1>
	<p>
	Para atingir o objetivo solicitado neste problema foi necessário inferir sobre o funcionamento do protocolo MQTT, a fim de integrar sensores com aplicações através deste. Com este projeto, o sistema desenvolvido auxiliou os graduandos em Engenharia da Computação a solidificar seus conhecimentos sobre integração de sistemas e adentrar mais profundamente ao universo de IoT (Internet das Coisas).</p>
<p>O produto implementado cumpre todos os requisitos solicitados, e foi desenvolvido e testado utilizando sensores acoplados a uma Raspberry Pi Zero.</p>
</div>
