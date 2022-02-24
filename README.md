# TCC-Arduino-Estacionamento-Inteligente-
Trabalho de conclusão de Curso onde o foco era resolver um problema ocorrente na sociedade, então foi decidido fazer um estacionamento inteligente em Arduino (C++) com sensores e motores.

Como o projeto foi realizado anos atrás e já não possuo o Arduino e seus componentes, decidi refaze-lo no Tinkercad de maneira simplificado e de fácil compreensão, segue abaixo o link do mesmo:

https://www.tinkercad.com/things/cq4EcScR015-estacionamento-inteligente-arduino

Obs:

Foi utilizado o Tinkercad apenas para fazer a simulação virtual do Projeto, porém o mesmo foi realizado presencialmente e feito através do Arduino e seus componente junto com uma maquete de um estacionamento para simular em situação real o projeto.

Explicação do Projeto: Para compor esse projeto foram utilizados o seguintes componentes:

Sensores de Distancia Ultrassónicos: Responsaveis por vérificar se tinham carros dentro das vagas. (Os dois sensores laterais foram representados como vagas e o central é responsavel por abrir a cancela se estiver carros para entrar no estacionamento, eles funcionam a partir da distancia, se estiver um carro menos de 180m então eles irão fazer o seu trabalho);

Mini Motor: Foi utilizado como cancela, para abrir o estácionamento caso estivesse com vagas disponiveis;

Display LCD: Foi utilizado para representar como um telão que mostra se o estacionamento possui vagas disponiveis, ocupadas e se está cheio;

LEDs (Vermelho e Verde): Representam a disponibilidade das vagas. (Vermelho ocupado e Verde disponivel);

Potenciômetro: Foi utilizado para controlador a iluminosidade do Display LCD;

Resistores: Foi utilizado para controlar a tensão sobre os LEDS.

Arduino e Protoboard: Onde o projeto foi montado.
