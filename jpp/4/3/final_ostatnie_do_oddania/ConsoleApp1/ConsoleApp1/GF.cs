
using System;

public class GF
{
    private long size = 1234567891;
    private long value;
    
    public GF()
    {
        value = 0;
    }

    public GF(long n)
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

    public static implicit operator long(GF gf)
    {
        return gf.value;
    }

    public long GetCharacteristic()
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

        long inverse = 1;
        for (long i = 1; i < obj_a.size; i++)
        {
            if ((obj_b.value * i) % obj_a.size == 1)
            {
                inverse = i;
                break;
            }
        }

        GF result = new GF();
        result.value = (long)((obj_a.value * inverse) % obj_a.size);
        return result;
    }
    
    
    
    
    public override string ToString()
    {
        return value.ToString();
    }
    
}
