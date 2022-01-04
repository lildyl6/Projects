package dirGraph;

import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
/*
Dylan Jones
lildyl6
116598378
0201
I pledge on my honor that I have not given or
received any unauthorized assistance on this assignment.
*/

/* This is the Vertex class. It represents a vertex in the graph.
 * The object holds a HashMap of its neighbors and a piece of data.
 * The neighbors represent edges.
*/



public class Vertex<V> 
{
	private Map<V, Integer> neighbors;
	
	// constructor for the Vertex object
	public Vertex()
	{
		neighbors = new HashMap<V, Integer>();
	}
	
	// adds a neighbor (edge) to the vertex
	public void addNeighbor(V destVertex, int weight)
	{
		if (destVertex == null)
		{
			throw new IllegalArgumentException();
		}
		
		// if it doesnt already exists it adds it
		if (!neighbors.containsKey(destVertex))
		{
			neighbors.put(destVertex, weight);
		}
	}
	
	// returns a boolean whether or not the vertex exists
	public boolean isNeighbor(V destVertex)
	{
		boolean result = false;
		
		// if the vertex is in its list of neighbors it returns true
		if (neighbors.containsKey(destVertex))
		{
			result = true;
		}
		
		return result;
	}
	
	// returns an edges weight
	public int getWeight(V vertex)
	{
		return neighbors.get(vertex);
	}
	
	// removes an edge/neighbor from a vertex
	public void removeNeighbor(V vertex)
	{
		if (vertex == null)
		{
			throw new IllegalArgumentException();
		}
		
		// if the edge exists it removes it
		if (neighbors.containsKey(vertex))
		{
			neighbors.remove(vertex);
		}
		
	}
	
	// returns a HashSet of neighbors of a Vertex
	public HashSet<V> getNeighbors()
	{
		HashSet<V> retSet = new HashSet<V>();
		
		for (V v : neighbors.keySet())
		{
			retSet.add(v);
		}
		
		return retSet;
	}
	
}
