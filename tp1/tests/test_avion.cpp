#include "Avion.h"
#include <assert.h>
#include "test_helper.h"
#include "test_avion.h"

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
	EstrategiaAvion eaire(AIRE);
	Avion avion1(eaire);
	avion1.accionar();
	EstrategiaAvion etierra(TIERRA);
	Avion avion2(etierra);
	avion2.accionar();
	TestHelper::instance().eval_test(true, "acciones realizables");
}



void test_serializacion() {
	
	TestHelper::instance().eval_test(true, "Test de serializacion Avion.");	
	
	EstrategiaAvion est(TIERRA);
	Avion avion(est);
	int prioridad;
	
	prioridad = avion.determinarPrioridad();
		
	const char* stream = avion.serializar();
	
	Avion nuevoAvion(stream);
	
	TestHelper::instance().eval_test(prioridad == nuevoAvion.determinarPrioridad(), "La prioridad del avion no se serializo correctamente");	
}

void PruebasAvion() {
	TestHelper::instance();
	PruebaComparacionAvion();
	PruebaAccionAvion();
	test_serializacion();
	TestHelper::cerrar();
}

