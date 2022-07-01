# Sonda de monitoreo para largos periodos de tiempo

## Pendientes

- Explorar modos de bajo consumo
  - Con plataforma FireBeetle el consumo en Deep Sleep fue cercano a 12uA y al despertarlo, alrededor de 40mA.
- Prueba unitaria sensor de intensidad lumínica MAX44009 en tarjeta GY-49:
  - https://didacticaselectronicas.com/index.php/sensores/luz/sensor-de-luz-ambiental-max44009-gy-49-sensores-de-luz-ambiente-ambiental-max44009-detail
  - Con las librerías utilizadas, había un error periódico de lectura donde el valor caía a 0,68 lumens durante unas lecturas y luego retornaba a valores correctos.
- Prueba unitaria sensor de temperatura DS18B20
  
  -La mediciones fueron aparentemente correctas todo el tiempo, incluso después del reinicio al terminar el modo deep sleep. 
  -El consumo con ambos sensores integrados fue de aproximadamente de 16uA en DeepSleep y de 60mA al activarse.
  -Con ambos sensores integrados y entrada al modo deep sleep periódica, se observó que el sensor de temperatura funcionaba correctamente y el de intensidad lumínica se alternaba entre mostrar el valor correcto de lectura y un 0 incorrecto después de cada reinicio.
- Prueba unitaria almacenamiento interno SPIFFS
  - Almacenar una marca de tiempo cada 5 segundos
  - Recuperar datos por el medio que sea
- Prueba unitaria a Dabble (ESP32 + Celular):
  - https://thestempedia.com/docs/dabble/getting-started-with-dabble/
    - Obtener posición del GPS
    - Obtener marca de tiempo para sincronizar reloj
