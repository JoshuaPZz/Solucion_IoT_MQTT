
Abstract—This paper proposes a method for timely identification of forest fires using NodeMCU ESP8266 microcontrollers and DHT22 environmental sensors. The system consists of two nodes: a sensor node that detects changes in temperature and humidity, and an alert node that displays data on an LCD screen and activates an audible alarm. Essential components such as the doorbell are analyzed and improvements such as advanced detection algorithms, extended wireless communication, and solar power options are suggested. Additionally, the MQTT protocol for device communication is examined, covering its features, quality of service levels, security, and case studies. MQTT brokers such as Eclipse Mosquitto, Mosca and EMQ are analyzed, along with a network topology for the system implementation. Finally, a test protocol is provided to evaluate the fire detection system.

INTRODUCCIÓN

    Los incendios forestales representan una de las mayores amenazas para el medio ambiente y las comunidades en todo el mundo. Su capacidad para causar devastación en la vida silvestre, el ecosistema y la infraestructura humana los convierte en un problema de gran relevancia. En este sentido, la detección temprana y la implementación de medidas preventivas y de respuesta son cruciales para mitigar el impacto negativo que estos fenómenos pueden causar. En respuesta a este problema, se propone un proyecto para desarrollar un sistema para detección y alerta de incendios forestales.

         II.  DEFINICIÓN DE PROBLEMÁTICA

    Cuando hablamos de los incendios forestales podemos concluir que son una amenaza muy importante para el medio ambiente y las comunidades. Por eso la detección y medidas contra este tipo de fenómenos de manera oportuna son cruciales para minimizar el daño que puedan causar. No obstante, la prevención es difícil debido a las dificultades de acceso a los bosques y la falta de sistemas de monitoreo.
  Posible Solución: 
    Como solución a esta problemática planteamos el desarrollo de un sistema, el cual se encargará de la detección y alerta de incendios forestales. Para su desarrollo utilizaremos microcontroladores NodeMCU ESP8266 y sensores ambientales; en específico contará con dos nodos principales (ESP8266): 


Nodo Sensor: 


Ubicado en un punto estratégico dentro del bosque. 
Cuenta con un sensor DHT22 encargado de medir y analizar la temperatura y humedad, 24/7. 
Detecta cambios repentinos en la temperatura específicamente el aumento de ella y la disminución de la humedad, lo que podría ser un indicio de un inicio de un incendio forestal. 
·         Al momento de detectar esta anomalía se enviará una señal al nodo alerta.   
2.                        Nodo Alerta: 
·         Se mantiene conectado a una red Wi-Fi o red telefónica. 
·         Recibe la señal del nodo sensor y la interpreta como una señal de un posible incendio. 
·         Muestra la información de tanto la temperatura como la humedad en una pantalla LCD 16x2. 
·         Genera la activación de un buzzer pasivo para generar una alarma sonora. 


 Componentes necesarios:

Imagen 1: NodeMCU ESP8266 (2) https://www.sigmaelectronica.net/wp-content/uploads/2017/12/New-Wireless-Module-CH340-NodeMcu-V3.jpg

Imagen 2: Sensor DHT22 (Temperatura y humedad) (1) https://www.sigmaelectronica.net/wp-content/uploads/imported/DHT22.jpg

Imagen 3: Buzzer Pasivo (1) https://www.steren.com.co/media/catalog/product/cache/b69086f136192bea7a4d681a8eaf533d/image/20313c1b1/buzzer-pasivo.jpg

Imagen 4: Protoboard (1) https://www.avs.la/imagenes/productos/normales/b/BOARWB102-R/color/1.jpg
Cosas que podrían complementar el sistema para su futuro desarrollo:
1. Para asegurarnos de que el funcionamiento del sistema sea el requerido implementamos algoritmos de detección de incendios. No obstante, se pueden incorporar algoritmos mas sofisticados para analizar tanto los datos de temperatura como humedad, teniendo en cuenta valores como la variabilidad estacional y las condiciones climáticas de donde se implemente el sistema.
     Lo mencionado anteriormente nos ayudaría a mejorar la precisión de la detección y reducir en la mayoría las falsas alarmas que se generen.
2. Comunicación inalámbrica de largo alcance, para mejorar la comunicación se podria utilizar módulos de comunicación inalámbrica de largo alcance tales como LoRA o LoRaWAN, estos se encaraian de ampliar la cobertura del sistema y permiten la implementación de esta en áreas remotas y sin acceso a redes telefónicas o Wi-Fi.
3. Integración con sistema de monitoreo existentes, para mejorar la compatibilidad del sistema, para que este pudiera integrarse con sistemas de monitoreo forestal existentes para generar una visión general de las condiciones ambientales y en específico la detección de incendios.
4. Alimentación solar, para hacerlo un sistema autosustentable y que en su mayoría no necesite de intervenciones en el sitio de instalación se puede implementar la energía solar para alimentar los nodos del sistema, haciendo de este sistema algo más amigable y sostenible en el ámbito ambiental.
5. Sensores adicionales, para mejorar el sistema puede darse la implementación de sensores de gases o cámaras para recopilar más datos sobre el territorio o sitio donde se encuentra implementado el sistema.
III. DIAGRAMAS

Imagen 5: Diagrama esquemático Buzzer-Nodo ESP8266

Imagen 6: Diagrama vista protoboard Buzzer-Nodo ESP8266  

Funcionamiento del circuito No.1:
      En las imágenes  5 y 6 el buzzer se activa mediante el pin D2  de la placa NodeMCU. Cuando este pin se establece en estado alto, el buzzer emite un sonido; cuando está en estado bajo, el buzzer está apagado. Esto dependerá del programa.

Conexiones esenciales del buzzer :
 -Pino positivo: Se conecta al pin  D2 de la placa NodeMCU para controlar el buzzer .
- Pino negativo: Se conecta al pin GND de la placa NodeMCU para completar el circuito y proporcionar una referencia de tierra.

Consideraciones adicionales:
 - Podría llegar a ser necesaria una resistencia de 100, conectada entre el pin D2 y el pin positivo del buzzer . Aunque no es estrictamente necesaria, esta resistencia puede ayudar a proteger tanto el buzzer como la placa NodeMCU de picos de corriente.
-     La variación en el tipo de buzzer utilizado puede afectar al sonido producido, así como la frecuencia y la duración del sonido programado en el código.

      Estos casos si se decide cambiar el buzzer utilizado o la fuente de poder.  

Imagen 7: Diagrama esquemático SensorTH -Nodo

Imagen 8: Diagrama vista protoboard SensorTH -Nodo ESP8266
Funcionamiento del circuito No.2:
     En las imágenes  7 y 8  se muestra la conexión entre el sensor DHT22  que mide la temperatura y humedad del aire, que está conectado y envía  los datos al pin DAT de la NodeMCU. La placa NodeMCU procesa estos datos a través del microcontrolador ESP8266. Para que posteriormente, los datos serán enviados a un servidor web o una aplicación móvil para su visualización o análisis.
Conexiones esenciales del sensor DHT22:
    DAT: Este pin transmite los datos de temperatura y humedad del sensor y se conecta al pin D2 de la placa NodeMCU.
