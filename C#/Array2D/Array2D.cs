using System;
using System.Collections.Generic;

/// <summary>
/// Static class with functions for 2D arrays
/// </summary>
public static class Array2D
{
    /// <summary>
    /// Returns a reference to the first entry in an array that fits the predicate
    /// </summary>
    /// <typeparam name="T"> Type of array </typeparam>
    /// <param name="array"> 2D array of type T </param>
    /// <param name="predicate"> Predicate function taking in a T object </param>
    /// <returns> A reference to a T object if an object fitting the predicate is found <br/>
    /// null otherwise </returns>
    #nullable enable
    public static T? Find<T>(T[,] array, Predicate<T> predicate) where T : class
    {
        for (int i = 0; i < array.GetLength(0); i++)
        {
            for (int j = 0; j < array.GetLength(1); j++)
            {
                if (predicate(array[i, j])) return array[i, j];
            }
        }
        return null;
    }

    /// <summary>
    /// Returns a list of references to all entries in a 2D array that fit a predicate
    /// </summary>
    /// <typeparam name="T"> Type of array </typeparam>
    /// <param name="array"> 2D array of type T </param>
    /// <param name="predicate"> Predicate function taking in a T object </param>
    /// <returns> A list of references to T objects if objects fitting the predicate (can be empty) </returns>
    public static List<T> FindAll<T>(T[,] array, Predicate<T> predicate)
    {
        List<T> items = new List<T>();

        for (int i = 0; i < array.GetLength(0); i++)
        {
            for (int j = 0; j < array.GetLength(1); j++)
            {
                if (predicate(array[i, j])) items.Add(array[i, j]);
            }
        }
        return items;
    }

    /// <summary>
    /// Tests if a 2D array is empty or not
    /// </summary>
    /// <typeparam name="T"> Type of array </typeparam>
    /// <param name="array"> 2D array of type T </param>
    /// <returns> true if the array is filled with only default T <br/>
    /// false otherwise </returns>
    public static bool IsEmpty<T>(T[,] array) where T : class
    {
        for (int i = 0; i < array.GetLength(0); i++)
        {
            for (int j = 0; j < array.GetLength(1); j++)
            {
                if (array[i, j] != default) return false;
            }
        }
        return true;
    }
}