<html>

<body>

<h1>Results:</h1>

<?php

$number1 = $_POST["number1"];
$number2 = $_POST["number2"];
$number3 = $_POST["number3"];
$number4 = $_POST["number4"];
$number5 = $_POST["number5"];

echo "Your guesses: ";

echo "$number1, $number2, $number3, $number4, $number5";

echo "<br />";

echo "<br />";

$y = array($number1, $number2, $number3, $number4, $number5);

$x = array();

echo "Random numbers: ";

for($i = 0; $i < 5; $i++)
{
	$x[$i] = rand(0, 20);
	for($j = 0; $j < $i; $j++)
	{
		if($x[$j] == $x[$i])
		{
			$i--;
			break;
		}
	}
}

//Generates the numbers and checks to make sure there are no repeats

$counter = 0;
$size1 = count($x);
$size2 = count($y);
for($i = 0; $i < $size1; $i++)
{
	echo "$x[$i], ";
	for ($j = 0; $j < $size2; $j++)
		if($x[$i] == $y[$j])
	{
		$counter++;
		break;
	}
}

//Counts mathches between 2 arrays not in same spot

echo "<br />";

echo "<br />";

echo "Matches: $counter"

?>

<form method="POST" action="lottery.php">
	<input type="submit" value="Again!" />

</form>

</body>

</html>
