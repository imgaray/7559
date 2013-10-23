#include "Avion.h"
#include <assert.h>
#include "test_helper.h"
#include "test_avion.h"

#include <iostream>

void PruebaComparacionAvion() {
	EstrategiaAvion eaire(AIRE);
	EstrategiaAvion etierra(TIERRA);
	Avion avion1(eaire);
	Avion avion2(etierra);
	Avion avion3(etierra);
	Avion avion4(eaire);
	TestHelper::instance().eval_test(avion2 < avion1, "avion tierra debe ser menor que avion aire");
	TestHelper::instance().eval_test(!(avion1 < avion2), "avion aire no debe ser menor que avion tierra");
	TestHelper::instance().eval_test(!(avion2 < avion3), "avion tierra no debe ser menor que avion tierra");
	TestHelper::instance().eval_test(!(avion1 < avion4), "avion aire no debe ser menor que avion aire");
}

void PruebaAccionAvion() {
	Avion avion1(AIRE);
	avion1.accionar();
	Avion avion2(TIERRA);
	avion2.accionar();
	TestHelper::instance().eval_test(true, "acciones realizables");
}



void test_serializacion() {
	
	TestHelper::instance().eval_test(true, "Test de serializacion Avion.");	
	Avion avion(TIERRA);
	int prioridad;
	
	prioridad = avion.determinarPrioridad();
		
	const char* stream = avion.serializar();
	
	Avion nuevoAvion(stream);
	
	TestHelper::instance().eval_test(avion.getEstrategia() == nuevoAvion.getEstrategia(), "Estrategia se conserva al serializar");
	TestHelper::instance().eval_test(prioridad == nuevoAvion.determinarPrioridad(), "Avion conserva la prioridad al serializar");	
	delete[] stream;
}

void PruebasAvion() {
	try {
		TestHelper::instance();
		PruebaComparacionAvion();
		PruebaAccionAvion();
		test_serializacion();
		TestHelper::cerrar();
	} catch(char const* ex) {
		std::cout << "error, exepcion levantada " << ex << std::endl;
	}
}

