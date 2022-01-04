#include "wstring-graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* This File contains a graph of names. It contains vertices and edges.
This is a weighted directed graph. The functions can add vertices
and edges to the graph. It is a dynamically allocated graph
implemented through a linked list */

/* prototype of the helper method I implemented */
static Vertex *get_vertex(const WString_graph *const graph, const char data[]);

/* prototype for project9 helper method */
static Edge* get_edge(const WString_graph* const graph, const char source[],
		      const char edge[]);

/* initializes the graph itself */
void init_graph(WString_graph *const graph)
{
  /* checks if its not null */
  if (graph)
  {
    graph->head = NULL;
    graph->num_vertices = 0;
  }
}

/* this function adds a new vertex to the graph */
int new_vertex_add(WString_graph *const graph, const char new_vertex[])
{
  int result = 0;
  Vertex *v;
  Vertex *curr;

  /* checks if graph isnt null and if the vertex already exists
     in the graph */
  if (graph && new_vertex && is_existing_vertex(graph, new_vertex) == 0)
  {
    /* dynamically allocates memory for the vertex and sets its fields */
    v = malloc(sizeof(Vertex));
    v->next = NULL;
    v->num_edges = 0;
    v->edges = NULL;
    v->data = malloc(strlen(new_vertex) + 1);
    /* copies the string over to the new vertex */
    strcpy(v->data, new_vertex);

    /* takes care of the first position insertion case */
    if (!graph->head || strcmp(v->data, graph->head->data) < 0)
    {
      /* inserts it first */
      v->next = graph->head;
      graph->head = v;
    }
    /* normal cases in the middle */
    else
    {
      curr = graph->head;

      /* goes through and finds where the vertex shoudl be
	 placed in the graph */
      while (curr->next && strcmp(v->data, curr->next->data) >= 0)
      {
        curr = curr->next;
      }

      /* sets the proper pointers to it */
      v->next = curr->next;
      curr->next = v;
      
    }

    /* increments the number of vertices in the graph */
    graph->num_vertices++;
    result = 1;
  }
      
  return result;
}

/* returns the number of vertices in the graph */
int num_vertices(const WString_graph *const graph)
{
  int result = 0;

  /* if the graph is null it just returns 0 */
  if(graph)
  {
    /* sets the return value to the number of vertices stored in
       the graph structure */
    result = graph->num_vertices;
  }

  return result;
}

/* checks to see if that vertex already exists in the graph */
int is_existing_vertex(const WString_graph *const graph, const char name[])
{
  int result = 0;

  /* uses helper method to locate vertex. if it doesnt exist the helper
     method returns null */
  if (get_vertex(graph, name))
  {
    result = 1;
  }
  
  return result;
}

/* returns an array of pointers of characters */
char **get_vertices(const WString_graph *const graph)
{
  Vertex* curr;
  char **v;
  int index = 0;

  if (graph)
  {
    /* dynamically allocates memory for the array */
    v = malloc(sizeof(char*) * (graph->num_vertices + 1));
    curr = graph->head;
    /* cycles through and dynamically allocates memory in the array the
       size of how long the string is times the size of a char */
    while (curr)
    {
      v[index] = malloc(strlen(curr->data) + 1);
      strcpy(v[index], curr->data);
      curr = curr->next;
      index++;
    }

    /* sets last element in array to null */
    v[index] = NULL;
  }
  /* if the graph is null it returns a null pointer */
  else
  {
    v = malloc(sizeof(char*));
    v[0] = NULL;
  }

  return v;
}

/* adds an edge between two vertices */
int add_edge(WString_graph *const graph, const char source[], const char dest[],
	     int cost)
{
  /* dynamically allocates memory for the edge */
  int result = 0;
  Vertex *temp;
  Edge *e;

  /* checks to see if the arguments are valid */
  if (graph && source && dest && cost >= 0)
  {
    new_vertex_add(graph, dest);
    new_vertex_add(graph, source);
    /* helper method to locate and manipulate a certain edge in the graph */
    temp = get_vertex(graph, source);
    
    if (get_weight_of_edge(graph, source, dest) != -1)
    {
      e = get_edge(graph, source, dest);
      e->weight = cost;
    }
    else
    {
      e = malloc(sizeof(Edge));

      /* sets fields */
      e->vertex = get_vertex(graph, dest);
      e->next = temp->edges;
      e->weight = cost;

      temp->edges = e;
      temp->num_edges++;
    }
    
    result = 1;
  }
  
  return result;
}

/* returns the weight of an edge */
int get_weight_of_edge(const WString_graph *const graph, const char source[],
		       const char dest[])
{
  /* default value if edge doesnt exist */
  int result = -1;
  Edge* e;

  if (graph && source && dest)
  {
    /* uses helper method to determine if the edge exists and then returns a
       pointer to it */
    e = get_edge(graph, source, dest);

    if (e)
    {
      /* using that pointer i can just grab the weight from it */
      result = e->weight;
    }
  }
  
  return result;
}

/* finds the number of edges a vertex has */
int num_neighbors(const WString_graph *const graph, const char vertex[])
{
  /* default value if graph of vertex is null*/
  int result = -1;
  Vertex *v;

  /* if graph and vertex isnt null */
  if (graph && vertex)
  {
    /* checks if the vertex exists  in the graph */
    if (is_existing_vertex(graph, vertex) == 1)
    {
      v = get_vertex(graph, vertex);
      result = v->num_edges;
    }
  }
  
  return result;
}

/* helper function for a few functions above. It simply finds and returns
   a specified vertex by name and returns a pointer to it. Its more
   effiecent to make this function than to repeat this code a few times */
static Vertex *get_vertex(const WString_graph *const graph, const char data[])
{
  Vertex* v = NULL;

  /* checks if graph is not null */
  if (graph)
  {
    /* checks if the graph has any vertices */
    if (graph->head)
    {
      v = graph->head;

      /* finds and returns pointer to vertex by cycling through until its found */
      while(v->next && strcmp(v->data, data) < 0)
      {
        v = v->next;
      }

      if (strcmp(v->data, data) != 0)
      {
        v = NULL;
      }
    }
  }

  return v;
}

/* project 9 part below */

/* deallocates the memory for the vertex list */
void free_vertex_list(char **const names)
{
  int k = 0;

  /* checks if names in not null */
  if (names)
  {
    /* cycles through and frees all the names */
    while (names[k])
    {
      free(names[k]);
      k++;
    }

    /* finally it frees the pointer to the array itself */
    free(names);
  }
}

/* deallocates memory for the entire graph */
void destroy_graph(WString_graph *const graph)
{
  Vertex* curr;
  Vertex* v;
  Edge* edge1;
  Edge* edge2;

  if (graph)
  {
    curr = graph->head;

    while (curr)
    {
      edge1 = curr->edges;

      while (edge1)
      {
	/* frees the edge */
	edge2 = edge1->next;
	free(edge1);
	edge1 = edge2;
      }

      /* frees the vertex and any data along with it */
      v = curr->next;
      free(curr->data);
      free(curr);
      curr = v;
    }
  }
}

/* removes an edge from the graph and deallocates the memory it used */
int remove_edge(WString_graph *const graph, const char source[], const char dest[])
{
  int result = 0;
  Vertex* source_vertex;
  Edge* edge1;
  Edge* edge2;
  
  if (graph)
  {
    /* checks if the edge is valid */
    if (get_weight_of_edge(graph, source, dest) != -1)
    {
      source_vertex = get_vertex(graph, source);
      edge2 = get_edge(graph, source, dest);

      if (source_vertex->num_edges == 1)
      {
	source_vertex->edges = NULL;
      }
      else
      {
	edge1 = source_vertex->edges;

	while (edge1->next != edge2)
	{
	  edge1 = edge1->next;
	}

	edge1->next = edge2->next;
      }

      /* frees the edge itself */
      free(edge2);
      source_vertex->num_edges--;
      result = 1;
    }
    
  }

  return result;
}

/* removes a vertex from the graph and deallocates memory assiciated with it */
int remove_vertex(WString_graph *const graph, const char vertex[])
{
  int result = 0;
  Vertex* source_vertex;
  Vertex* v;
  Edge* curr;
  Edge* next;
  char **vertices = get_vertices(graph);
  int i;
  int num_v;
  
  if (graph && vertex)
  {
    /* makes sure the vertex exists */
    if (is_existing_vertex(graph, vertex))
    {
      source_vertex = get_vertex(graph, vertex);
      curr = source_vertex->edges;

      /* frees all the vertex's edges */
      while(curr)
      {
	next = curr->next;
	free(curr);
	curr = next;
      }

      num_v = graph->num_vertices;

      for (i = 0; i < num_v; i++)
      {
	if (get_weight_of_edge(graph, vertices[i], vertex) >= 0)
	{
	  /* removes the edges from the graph from that vertex */
	  remove_edge(graph, vertices[i], vertex);
	}
      }

      if (source_vertex == graph->head)
      {
	graph->head = source_vertex->next;
      }
      else
      {
	v = graph->head;

	while(v->next != source_vertex)
	{
	  v = v->next;
	}

	v->next = source_vertex->next;
      }

      /* deallocates the memory of its fields and itself */
      free(source_vertex->data);
      free(source_vertex);
      graph->num_vertices--;
      result = 1;
    }
  
  }

  /* frees the vertex list */
  free_vertex_list(vertices);  
  
  return result;
}

/* returns an array of pointers of chars of all the edges of a vertex */
char **get_neighbors(const WString_graph *const graph, const char vertex[])
{
  Vertex *source_vertex;
  Edge *edge;
  char *temp_char;
  char **neighbors = NULL;
  int i = 0;
  int j = 0;
  int kill = 1;

  if (graph)
  {
    /* makes sure the vertex exists */
    if (is_existing_vertex(graph, vertex) == 1)
    {
      /* uses the helper method to get the vertex from the graph */
      source_vertex = get_vertex(graph, vertex);
      /* allocates memory for the array of pointers */
      neighbors = malloc(sizeof(char*) * (source_vertex->num_edges + 1));

      edge = source_vertex->edges;

      while (edge)
      {
	neighbors[i] = malloc(sizeof(char) * (strlen(edge->vertex->data) + 1));
	strcpy(neighbors[i], edge->vertex->data);
	edge = edge->next;

	i++;
      }

      neighbors[i] = NULL;

      /* kill is the killswitch and it gets turned off by default and only turns back on
	 when the loop is succesful and should continue */
      while (kill)
      {
	kill = 0;

	for (j = 0; j < source_vertex->num_edges - 1; j++)
	{
	  if (strcmp(neighbors[j], neighbors[j+1]) > 0)
	  {
	    temp_char = neighbors[j];
	    neighbors[j] = neighbors[j+1];
	    neighbors[j+1] = temp_char;
	    kill = 1;
	  }
	}
      }
      
    }
  }
  
  return neighbors;
}

/* helper method to find and return a certain edge. Easier and mor efficeint
   than repeating this code a few times */
static Edge* get_edge(const WString_graph* const graph, const char source[],
		      const char edge[])
{
  Vertex* v = get_vertex(graph, source);
  Edge* result = NULL;

  if (graph)
  {
    if (is_existing_vertex(graph, edge) == 1)
    {
      result = v->edges;

      while(result && strcmp(result->vertex->data, edge) != 0)
      {
	result = result->next;
      }
    }
  }

  return result;
}
 
