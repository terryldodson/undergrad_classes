//LAB 9: Write a search function that will search through a whole array and let the user know if that
//person is in the array or not. Looks at name, age, and gender, all three have to match (write in assembly). 
//Also write a median function that will print out the median number
//DATE: 10/29/18
//TAs: Daniel, Leroy, Jacob, Grace
//Students: Tyler Senter

.section .text
.global search

search: //searches through the array to find the person passed
//C++ Version:
//bool nameNotEqual;
//for(int i = 0; i < num_people; i++) {
	//for(int j = 0; j < 51; j++) {
		//if(people[i].name[j] != name[j])
		//nameNotEqual = true; 
		//break;
		
		//if(people[i].name[j] == '\0' || name[j] == '\0')
		//	 break;
	//}
		//if(nameNotEqual == true)
		//	continue;

	    //if(age != p.age)
        //  continue;

        //if(gender != p.gender)
        //  continue;

	//return &people[i]

//}

//Assembly Version:
	//initializing varaiable
	li t0, 0 //number of people in the array
	mv t1, a1
	
	li t2, 0 //number of people i have
	li t3, 51

	//outer for loop
	1:
		bge t0, t1, 1f
		li t2, 0 //sets j to equal 0 again
		//inner for loop
		2:
			bge t2, t3, 2f
			add t4, t2, a2 //t4 holds name of j (name plus j) j is t2, name is a2
			lb t4, 0(t4) //load first letter
			
			add t5, t2, a0 //increments to go to next letter (hols people of i dot name of j)
			lb t5, 0(t5) // load second letter

			bge t0, t1, 1f //says that if I go through entire array and theres not a match, jump to 1f
			//if statement
			3:
				bne t4, t5, 2f // checks to see if the names are equal
				beq t4, zero, 4f //checks to see if theres a 0 at end of t4, and if there is that means that we're at the end of the string
			3:
			addi t2, t2, 1 //j
			j 2b
		2: 
			addi t0, t0, 1 //if names doesn't equal, and 1 to i
			addi a0, a0, 60 //if names doesn't equal, go to next person (add 60 because thats the size of the structure)
			j 1b //end of inner for loop
		4:
			lw t6, 52(a0) //holds the age from the peoples array
			
			bne t6, a3, 2b //checks to see if the ages are equal (a3 - holds the age)
			j 5f
		
		5:
			lb a6, 56(a0) //holds the gender from the peoples array

			bne a6, a4, 2b //checks to see if the gender is equal (a4 - holds the gender) 
			ret //returns the name
	1:
	    mv a0, zero
		ret //returns the null

sort: //sorts the array

median: //finds the median in the array


