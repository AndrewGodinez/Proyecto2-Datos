# Proyecto II 

## Libreria grafica
Se uso **SFML** (la que trae ZinjaI en `mingw32-gcc6/sfml2`)

## Como compilar y ejecutar (ZinjaI)
1. Abrir `Proyecto-2-Datos.zpr` con ZinjaI (todos los `.h` y `.cpp` ya estan agregados al proyecto).
2. Usar la configuracion `Debug_Win32` o `Release_Win32`. 
3. Menu **Ejecucion > Limpiar** y luego **Ejecutar** (F9).

El programa debe ejecutarse con la carpeta del proyecto como directorio de trabajo (asi lo hace ZinjaI), porque ahi lee y guarda los archivos de datos. Si no los encuentra, el programa arranca sin datos.
La fuente se busca como `arial.ttf` en la carpeta del proyecto y si no existe se usa Arial de Windows.

## Archivos de datos
| Archivo | Formato |
|---|---|
| `ciudades.txt` | `codigo;nombre;x;y` |
| `rutas.txt` | `origen;destino;costo;duracion_horas` |
| `aeronaves.txt` | `codigo;modelo;capacidad;estado;placa;marca` |
| `tripulacion.txt` | `id;nombre;rol;disponible;aeronaveAsignada` |
| `vuelos.txt` | `codigo;origen;destino;hora;costo;duracion;aeronave;asientosOcupados` |
| `reservas.txt` | `id;cedula;nombre;origen;destino;rutaPasajero;rutaEquipaje;costo;duracion;activa;vuelos` |

El boton **Guardar Datos TXT** guarda todo. Al iniciar, el programa genera `reporte_sistema.txt`.

## Uso
En el mapa: clic en una ciudad = ORIGEN, clic en otra = DESTINO, clic en zona vacia = punto para una ciudad nueva. Al pasar el mouse sobre una ciudad se ven el costo y la duracion de sus rutas. Con la tecla de espacio pausa la animacion y con  esc limpia la seleccion.

| Pestaña | Que hace |
|---|---|
| 1. Rutas (Dijkstra) | Ruta mas barata o mas rapida, con escalas, totales y la ruta del equipaje.Y permite animar el vuelo. |
| 2. Destinos (Bellman-Ford) | Rutas minimas desde un origen a todas las ciudades (alcanzables y no alcanzables) y anima la ruta a un destino. |
| 3. Ciudades (ABB) | Busca una ciudad por nombre o codigo, muestra el arbol y anima los 4 recorridos. |
| 4. Reservar Vuelo | Elige criterio, muestra la ruta con los vuelos de cada tramo y crea la reserva. |
| 5. Flota y Tripulacion | Registra aeronaves y tripulantes, y asigna tripulantes a aeronaves. |
| 6. Pasajeros (AVL) | Busca una cedula con sus reservas, verifica si esta en un vuelo, muestra el AVL y anima recorridos. |
| 7. Minimos (Prim/Kruskal) | Arbol de expansion minima por costo (Prim) o por duracion (Kruskal) desde la ciudad ORIGEN, en el mapa y como arbol, con recorridos. |
| 8. Equipaje vs Tiempo | Compara la ruta del pasajero (menor tiempo) con la del equipaje (menor costo). |
| 9. Ciudades y Rutas | Agrega ciudades y agrega, modifica o elimina rutas. |
| 10. Vuelos y Pasajeros | Programa vuelos, lista los pasajeros de un vuelo y cancela reservas. |

## Estructuras de datos
| Mecanica | Estructura | Archivos |
|---|---|---|
| Ciudades y rutas | Grafo dirigido con matriz de adyacencia (costo y duracion por celda) | Grafo |
| Rutas minimas | Dijkstra con arreglos O(V^2) y Bellman-Ford O(V*E) | Dijkstra, BellmanFord |
| Reconstruir la ruta | Pila con nodos sobre el arreglo `padre` | Pila |
| Red minima | Prim por costo y Kruskal por duracion con conjuntos disjuntos | PrimKruskal, ConjuntoDisjunto |
| Ordenar aristas de Kruskal | Merge sort | Ordenamiento |
| Arbol de la red minima | Arbol general (hijos de cada ciudad), dibujado como primer hijo / siguiente hermano | PrimKruskal, VistaArbol |
| Recorridos por niveles | Cola con nodos | Cola |
| Ciudades de la red | Arbol binario de busqueda por nombre (sin distinguir mayusculas) | ArbolABB |
| Pasajeros y sus vuelos | Arbol AVL por cedula, cada nodo con una lista enlazada de reservas | ArbolAVL |
| Aeronaves, tripulacion, vuelos y reservas | Arreglos dentro de `Aerolinea` | Aerolinea, Modelos |

Otros archivos: `Aerolinea` (reglas del sistema), `Persistencia` y `Modelos` (archivos .txt), `Texto` (lectura y formatos), `Reporte`, y la interfaz: `App`, `PantallasCliente`, `PantallasAdmin`, `PantallasGestion`, `VistaMapa`, `VistaArbol`, `Animacion`, `Dibujo`, `Boton`, `CajaTexto`.
