# typed: true
# przy uzyciu Sorbet (type checker), aby byly typy generyczne
require 'sorbet-runtime'

class DHSetup

   
  extend T::Sig # zeby miec dostep do type_member
  extend T::Generic #  typ generyczny
  Elem = type_member # klasa DHSetup jest generyczna 
  
  def initialize
    @generator = generateGenerator
  end

  sig { returns(T) }
  def getGenerator 
    @generator 
  end 

  sig { params(a: T, b: Integer).returns(T) }
  def power(a, b)
    if b == 0 
      return T.new(1)
    end

    temp = power(a, b / 2)
    if b % 2 == 0
      temp * temp
    else
      a * temp * temp
    end
  end

  private

  @generator

  sig { returns(T) }
  def generateGenerator
    dum = T.new
    number = 1 + Random.rand(dum.getCharacteristics)
    T.new(number)
  end 

end
