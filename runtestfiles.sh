/******************************************************************************!
* @file     runtestfiles.sh
* @author   Léo Brückl <leo.bruckl@epfll.ch>            
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/
 
#!/bin/bash
for file in testfiles/*.txt; do
	./projet $file
done
