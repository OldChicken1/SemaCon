# SemaCon
A simple file-based database with a command-line interface is implemented. A hashtable data structure is 
used to store the id, which grant a fast access to the id (data). Starting hashtable size is set to 200. When
inserting more than 200 id, the program return ENOMEM and print out of memory. The hashtable size can be 
manually increased inside db.c.


# How to run?
<pre>
  Test: Build  and run the unit test by getting to /c-homework directory and issuing the following command  
          cmake -GNinja -DTARGET_GROUP=test {path-to-source_tree}  
          ninja -v  
          ctest --verbose  
  
  Main: Build and run the project by getting to /c-homework directory and issuing the following command  
          cmake -GNinja -DTARGET_GROUP=production {path-to-source_tree}  
          ninja-v  
          cd main  
          ./main  
</pre>

# Path to deliverables:
  main.c: /c-homework/main.c  
  db.c:   /c-homework/src/db.c  
  db.h:   /c-homework/src/db.h  
  test_db.c: /c-homework/test/suite_1/test_db.c  
          
