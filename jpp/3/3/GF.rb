class GF

  # konstruktor z defaultową wartoscia 0
  def initialize(n = 0)
    if n>= 0
      @value = n % @@size
    else
      @value = (@@size - (-n)) % @@size
    end
  end

  # do zwracania wartosci size
  def size
    @@size
  end

  # do zwracania wartosci value
  def value
    @value
  end

  # konwersje
  # self odnosi sie do obecnej instancji klasy, ktorej metoda jest wywolywana
  # no i mozna uzyc tego jako GF.to_GF(n)
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

  # prywatna czesc klasy
  private

  # @@, wiec jest to zmienna klasy
  @@size = 1234577

  # zmienna instancji
  @value




end
