(deftemplate permutation
	(multislot values)
	(multislot rest))
	
(defrule start-permutation
	(base-fact $?begin ?middle $?end)
	=>
	(assert (permutation (values ?middle)
						(rest ?end ?begin))))
						
(defrule continue-permutation
	(permutation (values $?done)
				 (rest $?begin ?middle $?end))
	=>
	(assert	(permutation (values ?done ?middle)
						 (rest ?begin ?end))))

(defrule print-permutation
	(permutation (values $?done) (rest))
	=>
	(printout t "Permutation is "  ?done crlf))