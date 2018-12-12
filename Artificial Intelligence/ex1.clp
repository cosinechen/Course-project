(deftemplate person
	(slot name)
	(slot address))
	
(deftemplate moved
	(slot name)
	(slot address))
	
(defrule process-moved-information ?f1 <- (moved (name ?name)(address ?address))
	?f2 <- (person (name ?name))
=>
	(retract ?f1)
	(modify ?f2 (address ?address)))
	
(deffacts example
	(person (name "John Hill")
	(address "25 Mulberry Lane"))
	(moved (name "John Hill")
	(address "37 Cherry Lane")))