# CodeAnalyzer
The focus of the project is to implement the software tools required for Code Analysis.
1. Built a Type Table by extracting the lexical code of source code. The Type table consists of information about the type definitions, Global functions etc. The information includes the fully qualified names and the files in which they are defined.
2.Performed Dependency analysis on all the source files. The Dependency analysis gives information about each file and the file it depends upon.
3. Traced the Strong components using TarjansAlgorithm. A strong component is the largest set of files that are all mutually dependent.
4. Stored all the Dependency information and Strong component information in a NoSQL Database(A Project which has been implemented by me).
5. The Database can be persisted on an XML and exported to any remote location. The Database can be retrieved back for any further analysis.
6. Efficient querying mechanism has been implemented so that dependencies of a file can be obtained in O(1) time from the NoSQL Database.
