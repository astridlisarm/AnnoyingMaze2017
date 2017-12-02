#include <iostream>
#include <fstream>
#include <string>
#include</home/astrid/Escritorio/ALEPH/tpl_graph.H>
#include <Dijkstra.H>
using namespace std;
#define VACIO   ' '
#define BLOQUE  '#'
char ** tablero;
int _filas;
int _columnas;
using Position = pair<int, int>;
using Node = Graph_Node<Position>;
using GT = List_Graph<Node>;

void createMaze(int filas,int columnas)
{
 	_filas = filas;
 	_columnas = columnas;   
  int vertices = 0;
  int x = 0;
  int y = 0;  

    tablero = new char* [filas];
    for( int i = 0 ; i < filas ; i++ )
        tablero[i] = new char [columnas];


  cout<<"CUantos vertices desea ingresar: "<<endl;
  cin>>vertices;
  for( int i = 0 ; i < vertices ; i++ )
    {
        cout<<"igrese posicion del vertice Numero: "<<i<<endl;
               cout<<"x: "<<endl;
               cin>>x;
               cout<<"y: "<<endl;
               cin>>y;
               tablero[x][y] =' ';
                              
    }

     for( int i = 0 ; i < _filas ; i++ )
    {
        for( int j = 0 ; j < _columnas ; j++ )
        {
            if(tablero[i][j] != ' ')
                tablero[i][j] = '#';
            
   
        }

      
    }
}



void dibujar()
{

    

      for( int i = 0 ; i < _filas ; i++ )
    {
        for( int j = 0 ; j < _columnas ; j++ )
        {
            switch(tablero[i][j])
            {
            
            case VACIO:
                cout << ' ';
                break;
            case BLOQUE:
                cout << '#';
                break;
            
            }
        }

        cout << endl;
    }

}

void CargarGraph(GT & g){
  
  GT d; //grafo al cual se le va a colocar el camino con Dijkstra
  Dijkstra_Min_Paths< GT > l; //Declarando objeto Dijkstra
	int x = 0;
	int y = 0;
  int xprev = 0;//posiciones previas al anterior nodo para conocer la distancia "entre nodos"
  int yprev = 0;
  int distance = 0;
	auto prev = g.insert_node(Position(x,y));
	auto start = prev;//nodo para especificar desde donde arrancar el Dijsktra
	auto next = g.insert_node(Position(x,y));

  for( int i = 0 ; i < _filas ; i++ )//recorro el board para saber la posicion de los vertices esquina
    {
        for( int j = 0 ; j < _columnas ; j++ )
        {
            if(tablero[i][j] == ' ')
            {
              
              next = g.insert_node(Position(i,j));
              
              if(xprev == i ){
                distance = j - yprev;
                for(int k = 0 ; k < j; k++){
                  tablero[i][k] = ' ';//simplemente abre camino en la consola
                }
              }

              if(yprev == j){
                distance = i - xprev;
                 for(int m = 0 ; m < i; m++){
                  tablero[m][j] = ' '; 
                }  
              }
              cout<<"Distance:---"<<distance<<endl;
              g.insert_arc(prev,next,distance);
              prev = next;
            xprev = i;
            yprev = j;
            
            }
           
        }

       
    }      
        

  next = g.insert_node(Position(_filas,_columnas));
	g.insert_arc(prev,next,6);
	 
	/* Usando funcion de Dijsktra en e cual g = es el grafo a buscar camino, star nodo de inicio,
  next es el nodo end y d el nuevo grafo con el camino minimo*/  

	l.compute_partial_min_paths_tree (g,start,next,d); 
	 

  // Itera sobre el conjunto completo de nodos
  for (GT::Node_Iterator it(d); it.has_curr(); it.next()) // mostrando grafo con camino de Dijkstra
    {
      auto p = it.get_curr();

      // Imprime la cantidad de arcos adyacentes a p
      cout << "Node " << (get<0>(p->get_info()), get<1>(p->get_info())) << ", "
	   << d.get_num_arcs(p) << " adjacent arcs: ";

      // Para el nodo que está visitando, itera sobre todos sus arcos adyacentes.
      for (GT::Node_Arc_Iterator ait(p); ait.has_curr(); ait.next())
	{
	  // Obtiene el nodo adyacente a p
	  auto q = ait.get_tgt_node();
	  
	  cout << (get<0>(q->get_info()), get<1>(q->get_info()))<<' ';
	   //q->get_info() << ' ';
	}

      cout << endl;
    }

  cout << endl << endl;

  // Imprime la cantidad total de arcos del grafo
  cout << d.get_num_arcs() << " arcs\n";

  // Itera sobre todos los arcos del grafo.
  for (GT::Arc_Iterator it(d); it.has_curr(); it.next())
    {
      auto a = it.get_curr();

    
      
      auto p = d.get_src_node(a);
      auto q = d.get_tgt_node(a);
      
      cout << (get<0>(p->get_info()), get<1>(p->get_info())) << " -- " << (get<0>(q->get_info()), get<1>(q->get_info()))<< endl;
    }
}
void print_graph(GT & g)
{
  // Imprime la cantidad de nodos del grafo
  cout << g.get_num_nodes() << " nodes\n";

  // Itera sobre el conjunto completo de nodos
  for (GT::Node_Iterator it(g); it.has_curr(); it.next())
    {
      auto p = it.get_curr();

      // Imprime la cantidad de arcos adyacentes a p
      cout << "Node " << (get<0>(p->get_info()), get<1>(p->get_info())) << ", "
	   << g.get_num_arcs(p) << " adjacent arcs: ";

      // Para el nodo que está visitando, itera sobre todos sus arcos adyacentes.
      for (GT::Node_Arc_Iterator ait(p); ait.has_curr(); ait.next())
	{
	  // Obtiene el nodo adyacente a p
	  auto q = ait.get_tgt_node();
	  
	  cout << (get<0>(q->get_info()), get<1>(q->get_info()))<<' ';
	   //q->get_info() << ' ';
	}

      cout << endl;
    }

  cout << endl << endl;

  // Imprime la cantidad total de arcos del grafo
  cout << g.get_num_arcs() << " arcs\n";

  // Itera sobre todos los arcos del grafo.
  for (GT::Arc_Iterator it(g); it.has_curr(); it.next())
    {
      auto a = it.get_curr();

    
      
      auto p = g.get_src_node(a);
      auto q = g.get_tgt_node(a);
      
      cout << (get<0>(p->get_info()), get<1>(p->get_info())) << " -- " << (get<0>(q->get_info()), get<1>(q->get_info()))<< endl;
    }
}
int main(){
	GT g;
	cout<<"ingrese numero de filas"<<endl;
  int rows = 0;
  int cols = 0;
  cin>>rows;
  cout<<"ingrese numero de cols"<<endl;
  cin>>cols;
	createMaze(rows,cols);
    
    CargarGraph(g);
    dibujar();
	//print_graph(g);
	return 0;
}
