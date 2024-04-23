namespace ConsoleApp1;

using System;

public class GF
{
    private int size = 1234567891;
    private int value;
    
    public GF()
    {
        value = 0;
    }

    public GF(int n)
    {
        if (n >= 0)
        {
            value = n % size;
        }
        else
        {
            value = ((size - (-n)) % size);
        }
    }

    public static implicit operator int(GF gf)
    {
        return gf.value;
    }

    public int GetCharacteristic()
    {
        return this.size;
    }
    
    public static bool operator ==(GF obj_a, GF obj_b)
    {
        return obj_a.value == obj_b.value;
    }

    public static bool operator !=(GF obj_a, GF obj_b)
    {
        return obj_a.value != obj_b.value;
    }

    public static bool operator <=(GF obj_a, GF obj_b)
    {
        return obj_a.value <= obj_b.value;
    }

    public static bool operator >=(GF obj_a, GF obj_b)
    {
        return obj_a.value >= obj_b.value;
    }

    public static bool operator <(GF obj_a, GF obj_b)
    {
        return obj_a.value < obj_b.value;
    }

    public static bool operator >(GF obj_a, GF obj_b)
    {
        return obj_a.value > obj_b.value;
    }    
    
    public static GF operator +(GF obj_a, GF obj_b)
    {
        GF result = new GF();
        result.value = (obj_a.value + obj_b.value) % obj_a.size;
        return result;
    }
    
    public static GF operator -(GF obj_a, GF obj_b)
    {
        GF result = new GF();
        result.value = (obj_a.value - obj_b.value + obj_a.size) % obj_a.size;
        return result;
    }

    public static GF operator *(GF obj_a, GF obj_b)
    {
        GF result = new GF();
        result.value = (obj_a.value * obj_b.value) % obj_a.size;
        return result;
    }
    
    public static GF operator /(GF obj_a, GF obj_b)
    {
        if (obj_b.value == 0)
        {
            throw new DivideByZeroException("Division by zero");
        }

        uint inverse = 1;
        for (uint i = 1; i < obj_a.size; i++)
        {
            if ((obj_b.value * i) % obj_a.size == 1)
            {
                inverse = i;
                break;
            }
        }

        GF result = new GF();
        result.value = (int)((obj_a.value * inverse) % obj_a.size);
        return result;
    }
    
    
    
    
    public override string ToString()
    {
        return value.ToString();
    }
    
}