require_relative "GF"

puts "Tworzę dwa obiekty: a i b"
a = GF.new
b = GF.new

puts "Ich obecne wartości to: a: #{a.value} b: #{b.value}"

a = GF.new(22)
puts "Podstawiam za a wartość 22: a: #{a.value}"

b = a
puts "Podstawiam a do b: b: #{b.value}"

puts "-------"
