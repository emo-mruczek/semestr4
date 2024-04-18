require_relative "GF"
require_relative "DHSetup"

dum = GF.new
dh = DHSetup[GF].new

puts "Wspolna liczba pierwsza: #{dum.characteristic}"
puts "Wspolny generator: #{dh.generator}"
