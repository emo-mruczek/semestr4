# typed: true
# przy uzyciu Sorbet (type checker), aby byly typy generyczne

class DHSetup[T]

  extend T::Sig  # do sygnatur metod
  #extend T::Generic # zeby miec dostep do type_member

  #Elem = type_member # klasa DHSetup jest generyczna 
  
  sig { returns(T) }
  def initialize
    @generator = generateGenerator
  end

  sig { returns(T) }
  def getGenerator 
    @generator 
  end 

  sig { params(a: T, b: Long).returns(T) }
  def power
    if b == 0 
      return T.new(1)

    temp = power(a, b / 2)
    if b % 2 == 0
      temp * temp
    else
      a * temp * temp

  private

  @generator

  sig { returns(T) }
  def generateGenerator
    dum = T.new
    number = 1 + Random.rand(dum.getCharacteristics)
    T.new(number)
  end 

end

