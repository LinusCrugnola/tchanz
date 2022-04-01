# Tchanz

ICC projet de Léo et Linus

# Snippets
## File Header:
```cpp
/****************************************************************!
  \file     filename
  \author   Léo Brückl, Linus Crugnola
  \date     date
  \brief    describtion
*****************************************************************/
```

# Notes

- Simulation gets in anthill phase
- anthill validation function creates anthill (with generator) and returns it to simulation
- get number of ants and decide if switch to ants or not
- anthill creation: anthill has ant-validation function
    - takes: &anthill, data
    - has: static counter and nbC nbD ...
    - creates ant and adds it to anthill
***

# Todo Anthill (Leo)

- to get propper formating on this you can click **"Open preview"** (Navigation bar on the right with magnifier) or hit: **ctrl+shift+v**

- create anthill vector in simulation (private member) like nutrition vector...
- rename state heap in simulation::decode_line (simulation.cc) to anthill (change enum as well)

In state anthill:
- call anthill data validation with **data (istringstream)** if it works with the stringstream it would be great because decode_line creates it anyway (line 28, the alternative is line as it is at the moment...) and with the vector of anthills of simulation:
```cpp
//function prototype proposition:
Anthill data_validation(istringstream data, const vector<Anthill>& hills);
```
- add a part to this function that verifies that a new anthill **doesn't intersect with the ones that are already existing** (iterate through vector and use function of squarecell square_superposition(square, square) to verify, this funtion returns a bool (see describtion in squarecell.h))
- after the function data_validation is called and it returns the Anthill object (in simulation::decode_line state anthill) add the object to the anthill vector (like above in nutrition state)
- if this fails (square_superposition returns false) you have to print the function:
```cpp
message::homes_overlap(h1,h2);
```
where as i understand the h's are the indices of the anthills (number in txt file), the order doesn't make a difference (the function changes it if necessairy) take care, the vector start at [0] but i think boulic would start at [1]...

after this the part of reading anthill data is finished, if you have time, the next step could be:

- change the states of collector, defensor... and create **one state** ant in simulation::decode line (change enum as well)
- in state anthill go to ant state if anthill is read (change state = collector to state = ant on line 67)
- get the number of ants (without generator) in state ant (function that you implemented in anthill) use the counter with the i's (top of function) to see which anthill of the vector should be used (i gives the number of anthills created)
- store this number of ants in the second counter (variable j and total_ants) (-> delete nbC, nbD, nbP and instead **generate total_ants** on line 35 (static!!!))
- make sure that j ants are generated (with j and total_ants) like in state nutrition and change state back to anthill or to finale depending on i and total (number of anthills to create) after all ants of one anthill are created (meanwhile I create the function that generates ants, you can let this empty)

## Holy shit t'es un chef si t'as réussi de faire tout ça!!!

```cpp
//in anthill data_validation:
//get square (position)
for(unsigned i=0; i<anthill.size(); i++){ //anthill is the vector
  if(square_superposition(anthill[i].position, position)){ //iterate over vector
    std::cout << message::homes_overlap(i+1, anthill.size()+1) << std::endl; //call error
  }
}
```


# Questions:
- data_validation: return pointer or class (Problem with destructor)?
- Describtion of functions: with @brief or just comment?
```cpp
/**
 * @brief function describtion
 */
void foo();
```
- store ants in different vectors or store them in one big vector (encapsulation...)?
- Unit tests in rendu or not?