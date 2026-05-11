
[ 🛠️  REQUISITOS ]

| Componente   | Requisito                             |
|--------------|---------------------------------------|
| OS           | Windows 10/11 con WSL 2               |
| Compilador   | g++ (GCC) en entorno Linux            |
| Intérprete   | Python 3.8+ en Windows                |
| Herramientas | netcat (nc), sed, dos2unix            |

---

[ GUÍA ]

1. PREPARAR EL FIREWALL (WINDOWS) (Si se bloquea la conexion por culpa del firewall)
   Para permitir que WSL se conecte al Host, ejecuta en PowerShell (Admin):
   > New-NetFirewallRule -DisplayName "Socket_SO" -Direction Inbound -LocalPort 12345 -Protocol TCP -Action Allow

2. CONFIGURAR LA IP DE CONEXIÓN
   Obtén la IP de la puerta de enlace de tu Windows desde la terminal de WSL:
   > ip route show | grep default | awk '{print $3}'
   *Nota: Sustituye este valor en "Practica 3_SO.cpp"*

3. EJECUCIÓN AUTOMATIZADA
   Ejecuta el script para limpiar formatos, compilar y correr el cliente:
   > chmod +x Ejecutar.sh
   > ./Ejecutar.sh

---

[ ESTRUCTURA DEL PROYECTO ]

* ServidorCamara.py         -> Emisor de datos binarios (B) en Windows.
* Practica 3_SO.cpp   -> Cliente C++ (Recepción byte a byte en WSL).
* Ejecutar.sh         -> Script de automatización (Limpieza + Compilación).
* datos_recibidos.txt -> Resultado final del proceso.
* .gitignore          -> Exclusión de binarios y temporales.

---

[ DETALLES DE IMPLEMENTACIÓN ]

1. FLUJO DE DATOS: 
   El servidor empaqueta enteros en bloques de 1 byte (struct.pack('B')). 
   El cliente lee exactamente 1 byte (unsigned char) por iteración para 
   evitar desalineamientos de memoria.

2. COMPATIBILIDAD CROSS-PLATFORM:
   Se utiliza 'sed' para convertir finales de línea CRLF (Windows) a LF 
   (Linux) automáticamente, evitando errores de ejecución en scripts.

3. RED VIRTUAL:
   La conexión se realiza a la IP virtual del Host (172.x.x.1) ya que 
   localhost en WSL apunta al propio contenedor Linux.

================================================================================
