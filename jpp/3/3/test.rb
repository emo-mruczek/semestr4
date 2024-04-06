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

puts "Czy a == b? #{a == b ? "prawda" : "fałsz"}"
puts "Czy a == 1? #{a == GF.to_GF(1) ? "prawda" : "fałsz"}"
puts "Czy a == 22? #{a == GF.to_GF(22) ? "prawda" : "fałsz"}"
puts "Czy a == 3? #{a == GF.to_GF(3) ? "prawda" : "fałsz"}"

puts "-------"

c = GF.new(12)
d = GF.new(0)

puts "Tworzę c: #{c.value} i d: #{d.value}"

puts "Czy a <= c? #{a <= c ? 'prawda' : 'fałsz'}"
puts "Czy a > c? #{a > c ? 'prawda' : 'fałsz'}"
puts "Czy a < 12? #{a < GF.to_GF(12) ? 'prawda' : 'fałsz'}"
puts "Czy a < d? #{a < d ? 'prawda' : 'fałsz'}"
puts "Czy 0 < a? #{GF.to_GF(0) < a ? 'prawda' : 'fałsz'}"
puts "Czy d < a? #{d < a ? 'prawda' : 'fałsz'}"

puts "-------"

e = a + b
puts "Tworzę e jako a + b: #{e.value}"

f = e + GF.to_GF(4)
puts "Tworzę f jako e + 4: #{f.value}"

g = GF.to_GF(4) + e
puts "Tworzę g jako 4 + e: #{g.value}"

h = f + GF.to_GF(-4)
puts "Tworzę h jako f + (-4): #{h.value}"

i = 6 + e.to_int
puts "Tworzę int i jako 6 + e: #{i}"

puts "-------"

h = GF.new(-1)
puts h.value

puts (h == GF.to_GF(-1) ? "prawda" : "fałsz")

puts "-------"

a = GF.new(2)
b = GF.new(3)
c = a * b
puts "Dla a = 2, b = 3, c = a * b: #{c.value}"

d = c * GF.new(4)
puts "d to c * 4: #{d.value}"

e = GF.new(4) * c
puts "e to 4 * c: #{e.value}"

i = 4 * c.to_int
puts "int i to 4 * c: #{i}"

puts "-------"

a = c / b
puts "a to c / b: #{a.value}"

a = c * GF.new(3)
puts "a to c * 3: #{a.value}"

a = GF.new(6) * b
puts "a to 6 * b: #{a.value}"

i = 18 / a.to_int
puts "int i to 18 / a: #{i}"

puts "-------"

