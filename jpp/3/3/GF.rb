#INPUT FOR NEGATIVE!!
class GF

  def value
    @value
  end

  def size
    @@size
  end

  # konstruktor z defaultową wartoscia 0
  def initialize(n = 0)
    if n>= 0
      @value = n % @@size
    else
      @value = (@@size - (-n)) % @@size
    end
  end

  # konwersje
  # self odnosi sie do obecnej instancji klasy, ktorej metoda jest wywolywana
  # no i mozna uzyc tego jako GF.to_GF(n)
  # w sumie moge po prostu uzywac GF.new(n), na jedno wychodzi
  def self.to_GF(n)
    new(n)
  end

  def to_int
    @value
  end

  # do zwracania charakterystyki
  def about
    puts "Size: #{@@size} Value: #{@value}"
  end

  # operatory porownan
  # ==
  def ==(obj)
    @value == obj.value
  end
  
  # !=
  def !=(obj)
    @value != obj.value
  end

  # <=
  def <=(obj)
    @value <= obj.value
  end

  # >=
  def >=(obj)
    @value >= obj.value
  end

  # <
  def <(obj)
    @value < obj.value
  end

  # >
  def >(obj)
    @value > obj.value
  end

  # operatory arytmetyczne
  # +
  def +(obj)
    puts
    res = (value + obj.value) % size
    GF.new(res)
  end

  # -
  def -(obj)
      res = (value - obj.value + size) % size
      GF.new(res)
  end

  # *
  def *(obj)
      res = (value * obj.value) % size
      GF.new(res)
  end

  # /
  def /(obj)
    if obj.value == 0
      raise ArgumentError, "Division by 0"
    else
      inverse = (1..size).find { |i| (obj.value * i) % size == 1 }
      res = (value * inverse) % size
      GF.new(res)
    end
  end

  #/ operatory podstawien
  # =
  def assign(obj)
    @value = obj.value
  end

  # zauwazylem w sumie, ze dzialaja te operatory bez definiowania ich tutaj

  # streamy
  def to_s
    @value.to_s
  end

  def from_input(input)
    temp = input.chomp.to_i
    @value = temp % @@size
    self
  end


  private
  # /prywatna czesc klasy
  # @@, wiec jest to zmienna klasy
  @@size = 1234577

  # zmienna instancji
  @value

end
