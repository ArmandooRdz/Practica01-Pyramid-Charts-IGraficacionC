
#  include <iostream>
#  include <GL/glew.h>
#  include <GL/freeglut.h>
//#  include <GL/glext.h>
//#pragma comment(lib, "glew32.lib") 
#include <cstdlib>
#include <time.h>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;



// Coordenadas limite del triángulo/pirámide:
#define PUNTO_A_X 10.0 //vertice izq
#define PUNTO_A_Y 20.0 
#define PUNTO_B_X 60.0 //vertice der
#define PUNTO_B_Y 20.0
#define PUNTO_C_X 35.0//vertice superior
#define PUNTO_C_Y 70.0

// Variables generales (datos de entrada)
string TITULO = "Grafico Piramidal en Base a los Datos del Archivo ";
int numeroDatos = 0;
//float datos[10] = {100.0,82.0,77.0,50,65.0,45.0,32.0,5.0};
float datos[10];
//string textoDatos[10] = {"Website Visit", "Download Page Visit", "Downloaded", 
//                                 "Interested To Buy", "Purchased", "Otro ejemplo", "Ejemplo2", "Sí otro"};
string textoDatos[10];
int numeroLineas = 0;
float posLineasTextoEnY = 15.0; // Posicion inicial del texto












// Dibujado texto letra por letra
void writeBitmapString(void *font, char *cadena){  
    char *c;
    for (c = cadena; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


void dibujarTitulo(string txt){
    // Pasar string a un arreglo de char
    char c[txt.size()+1];
    strcpy(c, txt.c_str());
    glColor3f(0.0, 0.0, 0.0); // Txt color
    glRasterPos3f(20.0, 92.0, 0.0); // Txt position
    writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, c); // Dibujado letra por letra. 
}




// Generador de numeros aleatorios para el color de cada bloque
float numeroAleatorio(){
    float nf = ((1.0 - 0.0) * ((float)rand() / RAND_MAX)) + 0.0; 
    return nf;
}



// Calcula la altura de cada bloque/trapecio dentro de la piramide
float alturaCarta(float dato){
   float sumaDatos = 0.0;
   for(int i = 0; i < numeroDatos; i++){
      sumaDatos += datos[i];
   }
   return dato/(sumaDatos/50); // la altura (y).
}





// Dibujado linea para unir el bloque con el texto.
//            Recibe el color del bloque,    posicion del bloque  y  posicion del texto
void dibujarLinea(float r, float g, float b, float bloqueX, float bloqueY, 
                        float txtX, float txtY){
                      
    glColor3f(r, g, b);// Set color line
    //glBegin(5.0); // Set point size
    
    glBegin(GL_LINES);
        glVertex3f(bloqueX, bloqueY, 0.0);
        glVertex3f(txtX, txtY, 0.0);
    glEnd();    
}




// Recive la cadena de texto, se establece la tipografia.
void drawString(string txt, float r, float g, float b, 
                    float bloqueX, float bloqueY) {

    posLineasTextoEnY += 8; // Espaciado entre cada texto

    glColor3f(0.0, 0.0, 0.0); // Color del texto
    glRasterPos3f(70, posLineasTextoEnY, 0.0); // Posicion del texto
    
    // Pasar string a un arreglo de char
    char c[txt.size()+1];
    strcpy(c, txt.c_str());

    writeBitmapString(GLUT_BITMAP_HELVETICA_18, c); // Dibujado letra por letra. 

   
    dibujarLinea(r, g, b, bloqueX, bloqueY, 70, posLineasTextoEnY+1); // Trazar la linea con el color del bloque
}





// Dibujado principal
void drawScene(){


    posLineasTextoEnY = 12; // Reinicio pos inicial del txt, en caso de redimensionar la ventana.
    string concatenacionTexto = ""; // Dato concatenado con el texto. Ej: "27% Download Page Visit".

    // Vertices superiores de cada bloque
    float verticeSupIzquierdoX = PUNTO_A_X;
    float verticeSupIzquierdoY = PUNTO_A_Y;    
    float verticeSupDerechoX = PUNTO_B_X;
    float verticeSupDerechoY = PUNTO_B_Y;
    // Color del bloque
    float r, g, b = 0.0;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0; i < numeroDatos; i++){

        // Generar color aleatorio para cada bloque
        r = numeroAleatorio();
        g = numeroAleatorio();
        b = numeroAleatorio();


        //color del bloque/trapecio
        glColor3f(r, g , b);

        // Dibujado de cada bloque/trapecio
        glBegin(GL_POLYGON);
            glVertex3f(verticeSupIzquierdoX, verticeSupIzquierdoY, 0.0);
            glVertex3f(verticeSupDerechoX, verticeSupDerechoY, 0.0);         
            glVertex3f(verticeSupDerechoX-alturaCarta(datos[i])/2, 
                            verticeSupDerechoY+alturaCarta(datos[i]), 0.0); 
            glVertex3f(verticeSupIzquierdoX+alturaCarta(datos[i])/2, 
                            verticeSupIzquierdoY+alturaCarta(datos[i]), 0.0);
        glEnd();
        
        // Guarda los vertices superiores de cada bloque/trapecio.
        // - vertice superior derecho:
        verticeSupIzquierdoX += alturaCarta(datos[i])/2;
        verticeSupIzquierdoY += alturaCarta(datos[i]);
        // - vertice superior izquierdo:
        verticeSupDerechoX += -alturaCarta(datos[i])/2;
        verticeSupDerechoY += alturaCarta(datos[i]);    


        concatenacionTexto = to_string((int)datos[i]); 
        concatenacionTexto.append("% ");
        concatenacionTexto.append(textoDatos[i]);

        // Dibujar cadena de texto y lineas para cada bloque. 
        // Se pasa el color para la linea de unión texto-bloque y las posiciones.

        drawString(concatenacionTexto, r, g, b, verticeSupDerechoX, verticeSupDerechoY-.5); 

    }
    
    dibujarTitulo(TITULO);

    glFlush();         

}



// Initialization routine.
void setup(void) {
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}



// OpenGL window reshape routine
void resize(int w, int h){
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}



// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y){
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}


// Imprime (por consola) la utilidad, informacion e indicaciones de la aplicacion.
void imprimirBienvenida(){
    printf("\n=======================================================\n");
    printf("\t\t   Grafico Piramidal\n");
    printf("=======================================================\n");
    printf("Esta aplicacion representa las relaciones de los datos\n"); 
    printf("de entrada mediante un grafico piramidal, tomando en\n");
    printf("cuenta el tamaño y la jerarquía de los mismos.\n\n");
    
    printf("Desarrollador: Armando Rodriguez Hernandez\n");
    printf("Institucion: Universidad Politecnica de Victoria\n");
    printf("Para la materia: Intro. Graficacion por Computadora\n\n");
    
    printf("-------------------------------------------------------\n");
    printf("\t       Indicaciones De Ejecucion\n");
    printf("-------------------------------------------------------\n");
    printf("Necesario:\n");
    printf(" - Mantener el archivo .txt en el directorio de programa\n");
    printf(" - Asegurese de que el archivo tenga un formato CSV\n   conteniendo la siguiente informacion:\n");
    printf("    * Datos numericos (10 como max. para una mejor\n       distribucion en pantalla alrededor de 7).\n");
    printf("    * Texto/Informacion de cada dato numerico\n");
    printf(" - Pasar el nombre del archivo como parametro\n\n");


}


bool muchasLineas(string c){
    int num = 0;
    for(int i = 0; i < c.size(); i++){
        if(c[i] == '\n'){
            num++;
        }
    }
    if(num > 10) {
        return true;
    }
    return false;
}


// Valida que solo se tenga 2 columnas (texto y dato numerico) no más.
bool masDeDosColumnas(string c){
    int n = 0; // Contador de columnas
    
    for(int i = 0; i < c.size(); i++){
        if(c[i] == ',') {
            cout<<"1ero"<<endl;
            if(n > 1) return true;
            n++;
            break;
        }
        if(c[i] == '\n'){
            cout<<"2do"<<endl;
            n = 0;
            break;
        }

    }

    cout<<"n = " <<n<<endl;

    return false;
}



bool validarEntradaDatos(string contenido){
    if(muchasLineas(contenido)){
        cout<<"1"<<endl;
        return false;
    }
    if(!masDeDosColumnas){
        cout<<"2"<<endl;
        return false;
    }
    

    return true;
}


bool esUnNumero(string str, int pos){
    return (str[pos] == '0' || str[pos] == '1' || str[pos-1] == '2' || str[pos] == '3' || str[pos] == '4' ||
        str[pos] == '5' || str[pos] == '6' || str[pos] == '7' || str[pos] == '8' || str[pos] == '9');
}


// Toma la cadena de entrada y convierte a string o float 
void parseoDeDatos(string c){
    int nDatos = 0; // Contador de '\n', lo que es igual al numero de datos.
    int contadorEspacios = 0;
    int contadorComas = 0;

    for(int i = 0; i < c.size(); i++){
        if(c[i] == '\n') {
            nDatos++;    
            contadorEspacios = 0;
            contadorComas = 0;
        }
        if(c[i] == ','){
            contadorComas++;
            contadorEspacios = 0;
        }
        if(nDatos > 10){
            printf("ERROR: Maximo numero de lineas superado.");
            return;
        }if(c[i] == ' '){
            contadorEspacios++;
            if(contadorEspacios > 2) return;
        }
    }
    numeroDatos = nDatos-1;  // Se lo asigna a la variable general. Menos la primer linea (encabezado)  


    int contadorTxtDatos = 0; // numero de cadenas en txtDatos[]
    int contadorDatosFloat = 0; // numeros de datos en datos[]
    string cadenaAux = ""; // temporal
    float numeroAuxFloat = 0.0; // temporal
    int stringOint = 0; // saber si anteriormente habia un salto de línea(\n), ó una coma(,)
    int contSaltosDeL = 0;
    
    for(int i = 0; i < c.size(); i++){ // Parseo y almacenamiento de las cadenas y numeros en las variables
        if((c[i] == '\n')){
            stringOint = 1;
            if(esUnNumero(c, i-1) && i > 0){
                numeroAuxFloat = stof(cadenaAux);
                datos[contadorDatosFloat] = numeroAuxFloat;
                contadorDatosFloat++;
                cadenaAux = "";
            }
        }
        else if(c[i] == ',' && (stringOint == 1)){  // guardar el string antes de la coma
            textoDatos[contadorTxtDatos] = cadenaAux;
            contadorTxtDatos++;
            cadenaAux = "";
            stringOint = 2; 
        }
        else if(stringOint == 1){ // leer cadena
            cadenaAux += c[i];
        }
        else if(stringOint ==  2){ // leer numeros
            cadenaAux += c[i];
            
        
        }
    }
    
}




bool lecturaFichero(char *parametro){
    string linea;// cada linea del archivo
    string c;
    fstream ficheroEntrada;
    
        
    ficheroEntrada.open(+parametro); // Se abre el archivo con el nombre argumento
        
    if(!ficheroEntrada){ // Si no se pudo abrir
        printf("\n> ERROR: No se pudo leer el fichero.\n\n");
        return false;
            
    }else{
        
        while (getline(ficheroEntrada, linea)){ // leer lnea por linea
            c += linea + "\n";
            numeroLineas++;
        }
    
        TITULO += parametro;
        if(!validarEntradaDatos(c)) { // Si no tiene un formato correcto

            printf("\nERROR: El fichero no tiene un formato correcto.\n");
            return false;

        }else{
            parseoDeDatos(c);
        }
    }

    ficheroEntrada.close();
 

    return true;
}







int main(int argc, char **argv) 
{

    imprimirBienvenida(); // Info e indicaciones de ejecucion

    if(argc <= 1){ // Si no se recibe parametro
        printf("\n> ERROR: Se necesita el nombre del archivo como parametro.\n\n");
        return 1;
    }
    if(!lecturaFichero(argv[1])){ // lectura del archivo
        return 1;
    }    


    glutInit(&argc, argv);



    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutInitWindowSize(900, 610);
    glutInitWindowPosition(200, 90); 
    glutCreateWindow("Pyramid Charts & Graphs");
    glutDisplayFunc(drawScene);  // Cada que se redimensiona la ventana se llama a drawScene
    glutReshapeFunc(resize);  
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup(); 
   
    glutMainLoop(); 
}
