NombreProgramaFuente=pyramid-v3
NombreFichero=ej1

rm $NombreProgramaFuente
g++ $NombreProgramaFuente.cpp -o $NombreProgramaFuente -lGL -lglut -lGLEW -lm
./$NombreProgramaFuente ej1.txt
