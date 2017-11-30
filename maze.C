#include <Dijkstra.H>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define VACIO   'B'
#define BLOQUE  'W'
char ** tablero;
int _filas;
int _columnas;
using Position = pair<size_t, size_t>;
using Node = Graph_Node<Position>;
using GT = List_Graph<Node>;
using Node1 = Graph_Node<char>;
using GT1 = List_Graph<Node1>;
void crearLaberinto(int filas,int columnas)
{
 	_filas = filas;
 	_columnas = columnas;   
    
    tablero = new char* [filas];
    for( int i = 0 ; i < filas ; i++ )
        tablero[i] = new char [columnas];
}

void construir(string filename)
{
    ifstream file(filename.c_str());

    int filas , columnas;

    file >> filas >> columnas;

    crearLaberinto(filas,columnas);

    for( int i = 0 ; i < filas ; i++ )
        for( int j = 0 ; j < columnas ; j++ )
        {
            file >> tablero[i][j];
                
        }

    file.close();
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

  int xprev = 0;//posiciones previas al anterior nodo para conocer la distancia "entre nodos"
  int yprev = 0;
  int ddistance= 0;
	int x = 0;
	int y = 0;
	auto prev = g.insert_node(Position(x,y));
	auto start = prev;
	auto next = g.insert_node(Position(x,y));

  for( int i = 0 ; i < _filas ; i++ )//recorro el board para saber la posicion de los vertices esquina
    {
        for( int j = 0 ; j < _columnas ; j++ )
        {
            if(tablero[i][j] == 'B')
            {
              
              next = g.insert_node(Position(i,j));
              
              if(xprev == i ){
                ddistance = j - yprev;
                
              }

              if(yprev == j){
                ddistance = i - xprev;
                
              }
              cout<<"Distance:---"<<ddistance<<endl;
              g.insert_arc(prev,next,ddistance);
              prev = next;
            xprev = i;
            yprev = j;
            
            }
           
        }

       
    }      
next = g.insert_node(Position(_filas,_columnas));
	g.insert_arc(prev,next,6);
	 

	 
	  GT d;
	  Path <GT> h = g;
	  Dijkstra_Min_Paths< GT > l;
   
// Trabajo en dijkstra aun

	  //l.compute_partial_min_paths_tree (g,start,next,d);
	 l.paint_partial_min_paths_tree(g,start,next);   
	 l.find_min_path(g,start,next,h);
   l.get_min_path(next, h);
	 //l.compute_min_paths_tree(g,next,d);
    for (Path <GT>::Iterator it(h); it.has_curr(); it.next())
    {
      auto item = it.get_curr();
      cout << "Node " << (get<0>(item->get_info()), get<1>(item->get_info())) << endl;

    }

  // Itera sobre el conjunto completo de nodos
  for (GT::Node_Iterator it(d); it.has_curr(); it.next())
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

	//print_graph(d);
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
	
	construir("laberinto.txt");
    dibujar();
    CargarGraph(g);
	//print_graph(g);
	return 0;
}
