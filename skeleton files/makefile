#----------
#Written by: Joaquin Carbonell, Jigarjeet Mannan
#For: CMPT 201 Assignment 3
#Lab Instructor: Philip Mees
#Lecture Instructor: Philip Mees
#makefile purpose: Hold commands for Assignment 3 makefile compiling
#----------

CC = gcc
CFLAGS = -Wall -std=c99 -g

Dbtest: dbTest.c DB.c DB.h DB_impl.c DB_impl.h
        $(CC) $(CFLAGS) $^ -o $@ -lm

valgrindDbtest: Dbtest
        valgrind --leak-check=yes ./Dbtest

testing/importDB: testing/testImport.c DB.c DB.h DB_impl.c DB_impl.h
        $(CC) $(CFLAGS) $^ -o $@

testing/exportDB: testing/testExport.c DB.c DB.h DB_impl.c DB_impl.h
        $(CC) $(CFLAGS) $^ -o $@

testing/countEntries: testing/testCountEntries.c DB.c DB.h DB_impl.c DB_impl.h
        $(CC) $(CFLAGS) $^ -o $@

testing/sortByMember: testing/testSortByMember.c DB.c DB.h DB_impl.c DB_impl.h
        $(CC) $(CFLAGS) $^ -o $@

testimportDB: testing/importDB
        ./$^ > testing/testImportDBOut.txt
        -diff testing/testImportDBOut.txt testing/correctImportDB.txt

testExportDB: testing/exportDB
        ./$^ > testing/testExportDBOut.txt
        -diff testing/testExportDBOut.txt testing/correctExportDB.txt

testCountEntries: testing/countEntries
        ./$^ > testing/testCountEntriesOut.txt
        -diff testing/testCountEntriesOut.txt testing/correctCountEntries.txt

testSortByMember: testing/sortByMember
        #./$^ > testing/testSortByMemberOut.txt
        ./$^
        -diff testing/testSortByMemberOut.txt testing/correctSortByMember.txt
        -diff testing/"Table Type" testing/correctTableType.txt
        -diff testing/"Surface Material" testing/correctSurfaceMaterial.txt
        -diff testing/"Structural Material" testing/correctStructuralMaterial.txt
        -diff testing/"Neighbourhood Name" testing/correctNeighbourhoodName.txt
        -diff testing/"Neighbourhood Id" testing/correctNeighbourhoodId.txt
        -diff testing/Ward testing/correctWard.txt

testing: testimportDB testExportDB testCountEntries testSortByMember

.PHONY: testing clean tar

clean:
        rm -f Dbtest testexport.csv vgcore.* testing/testImportDBOut.txt testing/importDB testing/testexport.csv testing/testExportDBOut.txt testing/exportDB testing/countEntries testing/testCountEntriesOut.txt testing/testSortBy>

tar: DESIGN.txt makefile dashboard.c DB.h DB.c DB_impl.h DB_impl.c PicnicTable.bin dbTest.c /testing
