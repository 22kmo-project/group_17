CREATE DATABASE  IF NOT EXISTS `atmdb` /*!40100 DEFAULT CHARACTER SET utf8 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `atmdb`;
-- MySQL dump 10.13  Distrib 8.0.26, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: atmdb
-- ------------------------------------------------------
-- Server version	8.0.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `id_account` int NOT NULL AUTO_INCREMENT,
  `account_number` char(18) NOT NULL,
  `balance` decimal(13,4) NOT NULL,
  `bank_name` varchar(45) NOT NULL,
  `account_type` char(6) NOT NULL,
  PRIMARY KEY (`id_account`),
  UNIQUE KEY `account_number_UNIQUE` (`account_number`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,'FI1222223333446789',1090.9900,'Osuuspankki','Debit'),(2,'FI1111112222333345',2000.0000,'Osuuspankki','Credit'),(3,'FI4522223333441298',780.8800,'Nordea','Debit');
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_right`
--

DROP TABLE IF EXISTS `account_right`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_right` (
  `id_account_right` int NOT NULL AUTO_INCREMENT,
  `id_account` int DEFAULT NULL,
  `id_user` int DEFAULT NULL,
  `account_holder` varchar(45) NOT NULL,
  `account_right` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id_account_right`),
  KEY `account_accountright_idx` (`id_account`),
  KEY `user_accountright_idx` (`id_user`),
  CONSTRAINT `account_accountright` FOREIGN KEY (`id_account`) REFERENCES `account` (`id_account`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `user_accountright` FOREIGN KEY (`id_user`) REFERENCES `user` (`id_user`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_right`
--

LOCK TABLES `account_right` WRITE;
/*!40000 ALTER TABLE `account_right` DISABLE KEYS */;
INSERT INTO `account_right` VALUES (1,1,1,'Pate Pätevä','Tero Terävä'),(2,2,1,'Pate Pätevä',NULL),(3,3,2,'Robert Large','');
/*!40000 ALTER TABLE `account_right` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `id_card` int NOT NULL AUTO_INCREMENT,
  `id_user` int DEFAULT NULL,
  `card_number` char(16) NOT NULL,
  `pin_code` varchar(255) NOT NULL,
  `card_access` tinyint(1) NOT NULL,
  PRIMARY KEY (`id_card`),
  UNIQUE KEY `card_number_UNIQUE` (`card_number`),
  KEY `user_card_idx` (`id_user`),
  CONSTRAINT `user_card` FOREIGN KEY (`id_user`) REFERENCES `user` (`id_user`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,1,'5555666677776789','0000',1),(2,2,'2222555511111298','0011',1);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card_right`
--

DROP TABLE IF EXISTS `card_right`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card_right` (
  `id_card_right` int NOT NULL AUTO_INCREMENT,
  `id_card` int DEFAULT NULL,
  `id_account` int DEFAULT NULL,
  PRIMARY KEY (`id_card_right`),
  KEY `card_cardright_idx` (`id_card`),
  KEY `account_cardright_idx` (`id_account`),
  CONSTRAINT `account_cardright` FOREIGN KEY (`id_account`) REFERENCES `account` (`id_account`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `card_cardright` FOREIGN KEY (`id_card`) REFERENCES `card` (`id_card`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card_right`
--

LOCK TABLES `card_right` WRITE;
/*!40000 ALTER TABLE `card_right` DISABLE KEYS */;
INSERT INTO `card_right` VALUES (1,1,1),(2,1,2),(3,2,2);
/*!40000 ALTER TABLE `card_right` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `id_transaction` int NOT NULL AUTO_INCREMENT,
  `id_account` int DEFAULT NULL,
  `transaction_date` datetime NOT NULL,
  `transaction_type` varchar(45) NOT NULL,
  `sum` decimal(13,4) NOT NULL,
  PRIMARY KEY (`id_transaction`),
  KEY `account_transaction_idx` (`id_account`),
  CONSTRAINT `account_transaction` FOREIGN KEY (`id_account`) REFERENCES `account` (`id_account`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=32 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,1,'2022-11-27 14:15:05','NOSTO',-40.0000),(2,1,'2022-11-20 16:15:05','NOSTO',-20.0000),(3,1,'2022-11-19 19:15:05','NOSTO',-100.0000),(4,1,'2022-11-19 12:15:05','TALLETUS',100.0000),(5,1,'2022-11-15 11:15:05','TALLETUS',20.0000),(6,1,'2022-11-10 09:15:05','TALLETUS',60.0000),(7,1,'2022-10-20 20:15:05','TILISIIRTO',-199.9900),(8,1,'2022-10-14 18:15:05','KORTTIOSTO',-9.9900),(9,1,'2022-10-07 08:15:05','KORTTIOSTO',-24.9900),(10,1,'2022-10-01 07:15:05','TILISIIRTO',-1200.0000),(11,1,'2022-09-05 22:15:05','PALVELUMAKSU',-2.0000),(12,1,'2022-09-02 10:15:05','PALVELUMAKSU',-3.5000),(13,2,'2022-11-25 23:15:05','E-LASKU',-159.8800),(14,2,'2022-11-25 23:15:05','E-LASKU',-159.8800),(15,2,'2022-09-01 18:15:05','TILISIIRTO',-100.0000),(16,2,'2022-07-10 11:15:05','KORTTIMAKSU',-5.9900),(17,2,'2022-06-09 16:15:05','KORTTIMAKSU',11.9900),(18,2,'2022-06-02 06:15:05','LUOTTOKORKO',25.0000),(19,3,'2022-11-25 14:15:05','NOSTO',-33.0000),(20,3,'2022-11-19 16:15:05','NOSTO',-20.0000),(21,3,'2022-11-17 19:15:05','NOSTO',-100.0000),(22,3,'2022-11-17 11:29:05','TALLETUS',150.0000),(23,3,'2022-11-15 11:05:05','TALLETUS',20.0000),(24,3,'2022-11-10 08:35:05','TALLETUS',60.0000),(25,3,'2022-10-20 20:52:05','TILISIIRTO',-199.9900),(26,3,'2022-10-14 18:11:05','KORTTIOSTO',-9.9900),(27,3,'2022-10-07 08:27:05','KORTTIOSTO',-24.9900),(28,3,'2022-10-01 07:35:05','TILISIIRTO',100.0000),(29,3,'2022-09-05 12:15:05','PALVELUMAKSU',-2.0000),(30,3,'2022-09-02 17:15:05','PALVELUMAKSU',-3.5000),(31,3,'2022-08-25 01:15:05','E-LASKU',-12.5900);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `id_user` int NOT NULL AUTO_INCREMENT,
  `username` varchar(45) NOT NULL,
  `user_fname` varchar(45) NOT NULL,
  `user_lname` varchar(45) NOT NULL,
  PRIMARY KEY (`id_user`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (1,'pp6789','Pate','Pätevä'),(2,'rl1298','Robert','Large');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'atmdb'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-11-28 17:55:39
