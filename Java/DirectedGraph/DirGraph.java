package dirGraph;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/*
Dylan Jones
lildyl6
116598378
0201
I pledge on my honor that I have not given or
received any unauthorized assistance on this assignment.
*/

/*
 * This is the DirGraph class. it represents a graph of vertices and edges.
 * The object just holds a HashMap of vertices with a value as a key
 */

public class DirGraph<V> 
{
	// only field
	private Map<V, Vertex<V>> vertices;
	
	// constructor for DirGraph object
	public DirGraph()
	{
		vertices = new HashMap<V, Vertex<V>>();
	}
	
	// creates a vertex and adds it to the graph/ Map of vertices
	public boolean createVertex(V vertexData) 
	{
		// every method with V input data checks if they're null
		if (vertexData == null)
		{
			throw new IllegalArgumentException();
		}
		
		// initial return value
		boolean result = false;
		
		// if it isn't already a vertex it creates one and returns true
		if (!isVertex(vertexData))
		{
			vertices.put(vertexData, new Vertex<V>());
			result = true;
		}
		
		return result;
	}

	// checks to see if that data is alreadyan existing vertex
	public boolean isVertex(V vertexData) 
	{
		if (vertexData == null)
		{
			throw new IllegalArgumentException();
		}
		
		boolean result = false;
		
		// if the list of vertices contains this vertexData it returns true
		if (vertices.containsKey(vertexData))
		{
			result = true;
		}
		
		return result;
	}

	// returns a HashSet of vertices for the graph
	public Collection<V> getVertices() 
	{
		HashSet<V> retVertices = new HashSet<V>();
		
		// transfers all the elements from the keySet over to a HashSet
		for (V v : vertices.keySet())
		{
			retVertices.add(v);
		}
		
		// returns the newly added to HashSet
		return retVertices;
	}

	// deletes a vertex that has edges
	public boolean deleteVertexWithEdges(V vertexData) 
	{
		if (vertexData == null)
		{
			throw new IllegalArgumentException();
		}
		
		boolean result = false;
		
		// if the vertex exists it gets removed from the graph
		if (isVertex(vertexData))
		{
			vertices.remove(vertexData);
			result = true;
		}
		
		return result;
	}

	// creates an edge between two vertices with a weight
	public boolean createEdge(V sourceVertex, V destVertex, int weight) 
	{
		if (sourceVertex == null || destVertex == null)
		{
			throw new IllegalArgumentException();
		}
		
		boolean result = false;
		
		// checks to see if wieght is in the valid parameters and
		// if there isnt already an edge there
		if (weight >= 0 && getEdge(sourceVertex, destVertex) == -1)
		{
			// both of these ifs check to see if these vertices exist
			// and if not they are created
			if (!isVertex(sourceVertex))
			{
				createVertex(sourceVertex);
			}
			
			if (!isVertex(destVertex))
			{
				createVertex(destVertex);
			}
			
			// creates a new vertex if that one if null
			if (vertices.get(sourceVertex) == null)
			{
				vertices.put(sourceVertex, new Vertex<V>());
			}
			
			// puts the dest vertex in the source vertex's list of neighbors
			vertices.get(sourceVertex).addNeighbor(destVertex, weight);
			
			result = true;
		}
		
		
		return result;
	}

	// gets the weight value associated with an edge
	public int getEdge(V sourceVertex, V destVertex) 
	{
		if (sourceVertex == null || destVertex == null)
		{
			throw new IllegalArgumentException();
		}
		
		// initial result
		int result = -1;
		
		// checks to see if both are vertices and not null
		if (isVertex(sourceVertex) && isVertex(destVertex) &&
				vertices.get(sourceVertex) != null)
		{
			// if they are neighbors it gets the weight of the edge
			if (vertices.get(sourceVertex).isNeighbor(destVertex))
			{
				result = vertices.get(sourceVertex).getWeight(destVertex);
			}
		}
		
		// returns the weight of the edge
		return result;
	}

	// changes the weight of an edge
	public boolean changeEdge(V sourceVertex, V destVertex, int newWeight) 
	{
		if (sourceVertex == null || destVertex == null)
		{
			throw new IllegalArgumentException();
		}
		
		boolean result = false;
		
		// checks to see if the edge is there
		if (getEdge(sourceVertex, destVertex) >= 0)
		{
			// removes the edge
			vertices.get(sourceVertex).removeNeighbor(destVertex);
			
			// if the new weight is >= -1 it adds a new edge in that
			// place with the new weight
			if (newWeight >=0)
			{
				vertices.get(sourceVertex).addNeighbor(destVertex, newWeight);
			}
			
			result = true;
		}
		
		return result;
	}

	// returns a HashSet of the neighbors of a vertex
	public Collection<V> neighborsOfVertex(V vertexData) 
	{
		if (vertexData == null)
		{
			throw new IllegalArgumentException();
		}
		
		// sets it equal to null as a default return
		HashSet<V> retList = null;
		
		// if the vertex exists it goes to the vertex class to get a
		// HashSet of the neighbors to decrease visibility
		if (isVertex(vertexData))
		{
			retList = vertices.get(vertexData).getNeighbors();
		}
		
		return retList;
	}

	// splits up a graph into two different graphs containing the passed
	// in vertices present in the original graph
	public DirGraph<V> divideGraph(Collection<V> verticesOfNewGraph) 
	{
		if (verticesOfNewGraph == null)
		{
			throw new IllegalArgumentException();
		}
		
		// creates a new graph
		DirGraph<V> retGraph = new DirGraph<V>();
		
		// iterates through the current graphs vertices
		for (V v : getVertices())
		{
			// iterates through the vertices of the new graph
			for (V newV : verticesOfNewGraph)
			{
				// if they are equal it gets added
				if (v.equals(newV))
				{
					// iterates through its neighbors to find any matches
					for (V neighbor : neighborsOfVertex(v))
					{
						// creates the vertex
						retGraph.createVertex(newV);
						
						// if the neighbor is there it gets added to the
						// new graph between those vertices
						if (verticesOfNewGraph.contains(neighbor))
						{
							retGraph.createEdge(newV, neighbor, getEdge(
									v, neighbor));
						}
					}
				}
			}	
		}
		
		// iterates through the vertices of the new graph and the old graph
		// and if any are equal they get deleted from the old graph
		for (V v : getVertices())
		{
			for (V newV : verticesOfNewGraph)
			{
				if (v.equals(newV))
				{
					deleteVertexWithEdges(v);
				}
			}
		}
		
		return retGraph;
	}

}
