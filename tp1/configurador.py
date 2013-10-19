def get_input(texto, tipo, intentos = 3):
	while(intentos != 0):
		try:
			return tipo(raw_input(texto))
		except:
			print "por favor ingrese un " + tipo
			intentos -= 1
			if (intentos == 0):
				raise "intentos agotados"
try:
	av1 = get_input("ingrese los aviones a aterrizar: ", int)
	av2 = get_input("ingrese los aviones a despegar: ", int)
	torres = get_input("ingrese los operadores de torre: ", int)
	pistas = get_input("ingrese las pistas: ", int)
	config = open(".cnfg", "w")
	config.write("aviones-aire="+ str(av1)+"\n")
	config.write("aviones-tierra="+ str(av2) + "\n")
	config.write("controladores="+ str(torres) + "\n")
	config.write("pistas="+str(pistas) + "\n")
	config.close()
except:
	print "error en la configuracion, intentelo de nuevo"

