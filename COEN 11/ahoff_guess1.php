<html>

<body>

<h1>Your Guess:</h1>

<?php
$number1 = $_POST["number1"];

echo "$number1";

echo "<br/>";

echo "<br/>";

$guess = array();

for($i = 0; $i < 5; $i++)
	{
	$guess[$i] = rand(1, 20);
	echo "Random Numbers $guess[$i]";
	echo "<br/>";
	}

echo "<br/>";

$counter = 0;
$size = count($guess);
for($i = 0; $i < $size; $i++){
	if($number1 == $guess[$i])
		{
		echo "You Got It!";
		break;
		}
	else
		{
		$counter++;
		}
}
if ($counter > 0)
	echo "Wrong!"
?>

<form method="POST" action="ahoff_guess.php">
	<input type="submit" value="Again!" />
</form>

</body>

</html>
