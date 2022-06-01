# Processo Seletivo Origem!

## Funcionalidades Implementadas:
	- Classes:
		- Bateria:
			- Associar/Desassociar host = setHost(Host* _host)
			- Acesso a todos os atributos = set/get-uid/soc/host
			
		- Moto:
			- Ligar e desligar a moto = turnOn/Off
			- Associar/Liberar bateria = attatch/detatchBattery
			- Acionar/soltar Acelerador = setAccelerator()
			- Acionar/soltar Freio = setBreaker()
			- Acesso a todos os atributos = set/get plate/speed/battery

		- Estação de Troca de Bateria (ETB):
			- Associar/Liberar Bateria = att/dttBattToCP()
			- Acionar/desligar carregamento = initChgBattOnCP()
			- Numero de bateria presentes = getAmountOfBattTotal()
			- Numero de bateria carregando = getAmountOfBattCharging()
			- Acesso a todos os atributos  set/get uid/cps


		- Ponto de Carga (CP):
			- Associar/Liberar Bateria = detatch/attatchBattery()
			- Acesso a todos os atributos  set/get battery/state