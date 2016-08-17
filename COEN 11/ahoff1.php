<html>

<body>

<?php
$number1 = $_POST["number1"];
$number2 = $_POST["number2"];
$number3 = $_POST["number3"];

echo "$number1 x $number2";
echo "<br />";
$number4 = ($number1) * ($number2);

if($number3 == ($number1*$number2))
	echo "Correct!";
else
	echo $number4;
?>

<form method="POST" action="ahoff.php">
	<input type="submit" value="Mo Multiplication!" />
</form>

</body>

</html>

