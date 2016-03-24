<?PHP
	
	include 'db_config.php';

	$db_handle = mysql_connect($server, $user_name, $password);

	$db_found = mysql_select_db($database, $db_handle);

	if ($db_found) {
		$SQL = "SELECT * FROM tb_temperature";
		$result = mysql_query($SQL);
		$id;
		$date;
		$time;
		$temp;

		while ( $db_field = mysql_fetch_assoc($result) ) {

			$id = $db_field['ID'] . "<BR>";
			$date = $db_field['Date'] . "<BR>";
			$temp = $db_field['Value'] . "<BR>";
			
		}
		mysql_close($db_handle);
	}
	else {
		print "Database NOT Found ";
	}

?><!DOCTYPE HTML>
<html>
<head>
    <meta charset="utf-8">
    <title>Temperature</title>
</head>
<body>
	<H2> TEMPERATURE </H2>
	<H3> <?php echo $temp; ?>*C </H3>
	<H3> <?php echo $date; ?> </H3>
</body>
</html>