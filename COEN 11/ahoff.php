<html>

<h1>Multiplication Test</h1>

<h2>Write the correct answer then click the Calculate button to see if your answer is correct</h2>

<body>

<?php

$number1 = rand(0, 12);

//echo "number1"

//$echo "x"

$number2 = rand(0, 12);

//echo "number2"

echo "$number1 x $number2";

?>

<form action="ahoff1.php" method="POST">
	<input type= "hidden" name="number1" value=<?php echo $number1; ?> />
	<input type= "hidden" name="number2" value=<?php echo $number2; ?> />
	<input type= "number" name="number3" />
	<input type= "submit" value="Calculate!" />
</form>

</body>

</html>
