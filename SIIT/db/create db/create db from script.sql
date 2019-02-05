USE [DB_FIXED_ASSET]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Room_SearchByTID]    Script Date: 13/1/2562 23:11:30 ******/
DROP PROCEDURE [dbo].[Sp_Room_SearchByTID]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Room_SearchByRoomCode]    Script Date: 13/1/2562 23:11:30 ******/
DROP PROCEDURE [dbo].[Sp_Room_SearchByRoomCode]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Room_Save]    Script Date: 13/1/2562 23:11:30 ******/
DROP PROCEDURE [dbo].[Sp_Room_Save]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_SearchByTid]    Script Date: 13/1/2562 23:11:30 ******/
DROP PROCEDURE [dbo].[Sp_Asset_SearchByTid]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_SearchByFid]    Script Date: 13/1/2562 23:11:30 ******/
DROP PROCEDURE [dbo].[Sp_Asset_SearchByFid]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_Save]    Script Date: 13/1/2562 23:11:30 ******/
DROP PROCEDURE [dbo].[Sp_Asset_Save]
GO
/****** Object:  Table [dbo].[TB_ROOM]    Script Date: 13/1/2562 23:11:30 ******/
DROP TABLE [dbo].[TB_ROOM]
GO
/****** Object:  Table [dbo].[TB_ASSET]    Script Date: 13/1/2562 23:11:30 ******/
DROP TABLE [dbo].[TB_ASSET]
GO
USE [master]
GO
/****** Object:  Database [DB_FIXED_ASSET]    Script Date: 13/1/2562 23:11:30 ******/
DROP DATABASE [DB_FIXED_ASSET]
GO
/****** Object:  Database [DB_FIXED_ASSET]    Script Date: 13/1/2562 23:11:30 ******/
CREATE DATABASE [DB_FIXED_ASSET]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'DB_FIXED_ASSET', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL12.SQLSERVER_2014\MSSQL\DATA\DB_FIXED_ASSET.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'DB_FIXED_ASSET_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL12.SQLSERVER_2014\MSSQL\DATA\DB_FIXED_ASSET_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [DB_FIXED_ASSET].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [DB_FIXED_ASSET] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET ARITHABORT OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET  DISABLE_BROKER 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET  MULTI_USER 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [DB_FIXED_ASSET] SET DB_CHAINING OFF 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [DB_FIXED_ASSET] SET DELAYED_DURABILITY = DISABLED 
GO
USE [DB_FIXED_ASSET]
GO
/****** Object:  Table [dbo].[TB_ASSET]    Script Date: 13/1/2562 23:11:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_ASSET](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[ASSET_TID] [nvarchar](50) NOT NULL,
	[ROOM_CODE] [nvarchar](50) NULL,
	[ASSET_EPC] [nvarchar](50) NULL,
	[ASSET_FID] [nvarchar](50) NULL,
	[ASSET_LABEL] [nvarchar](200) NULL,
	[ASSET_TYPE] [nvarchar](200) NULL,
	[ASSET_DESCRIPTION] [nvarchar](1000) NULL,
 CONSTRAINT [PK_TB_ASSET] PRIMARY KEY CLUSTERED 
(
	[ASSET_TID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[TB_ROOM]    Script Date: 13/1/2562 23:11:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_ROOM](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[ROOM_CODE] [nvarchar](50) NULL,
	[ROOM_TID] [nvarchar](50) NULL,
	[ROOM_EPC] [nvarchar](50) NULL,
	[ROOM_DESCRIPTION] [nvarchar](1000) NULL,
 CONSTRAINT [PK_TB_ROOM] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[TB_ASSET] ON 

INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (5, N'1111', N'111', NULL, NULL, NULL, NULL, NULL)
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (6, N'11111', N'111', NULL, NULL, NULL, NULL, NULL)
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (1, N'123456', N'1234', N'1234', N'1234', N'1234', N'1234', N'1234')
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (7, N'2222', N'111', NULL, NULL, NULL, NULL, NULL)
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (8, N'33333', N'111', NULL, NULL, NULL, NULL, NULL)
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (9, N'4444', N'111', NULL, NULL, NULL, NULL, NULL)
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (10, N'5555', N'111', NULL, NULL, NULL, NULL, NULL)
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (11, N'6666', N'111', NULL, NULL, NULL, NULL, NULL)
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (2, N'e11111', N'111', N'', N'111', N't', N'', N'd')
INSERT [dbo].[TB_ASSET] ([ID], [ASSET_TID], [ROOM_CODE], [ASSET_EPC], [ASSET_FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION]) VALUES (3, N'e22222', N'111', N'', N'222', N't1', N'', N'd1')
SET IDENTITY_INSERT [dbo].[TB_ASSET] OFF
SET IDENTITY_INSERT [dbo].[TB_ROOM] ON 

INSERT [dbo].[TB_ROOM] ([ID], [ROOM_CODE], [ROOM_TID], [ROOM_EPC], [ROOM_DESCRIPTION]) VALUES (5, N'5555', N'555555', N'5555', N'5555')
INSERT [dbo].[TB_ROOM] ([ID], [ROOM_CODE], [ROOM_TID], [ROOM_EPC], [ROOM_DESCRIPTION]) VALUES (6, N'111', N'r11111', N'', N'')
SET IDENTITY_INSERT [dbo].[TB_ROOM] OFF
/****** Object:  StoredProcedure [dbo].[Sp_Asset_Save]    Script Date: 13/1/2562 23:11:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[Sp_Asset_Save] -- !!! สำคัญ ต้องเปลี่ยน Activity type
	@RoomCode nvarchar(50),	
	@Epc nvarchar(50),	
	@Tid nvarchar(50),	
	@Fid nvarchar(50),	
	@AssetLabel nvarchar(200),	
	@AssetType nvarchar(200),	
	@AssetDescription nvarchar(1000),	
	@RowCount int output,
	@MessageResult nvarchar(100) output
AS
BEGIN

	-- ===================================================================================
	-- STATE-1: VALIDATION
	--             - CHECK NULL
	--             - CHECK EMPTY
	-- ===================================================================================
	
	-- TID
	IF @Tid is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end	
	IF @Tid=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end	
	-- FID
	IF @Fid is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid FID! FID cannot be null.';
		return -2;
	end	
	IF @Fid=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid FID! FID cannot be empty.';
		return -2;
	end	

	-- ===================================================================================
	-- STATE-2: SAVE BY INSERT OR UPDATE
	-- ===================================================================================	
	Declare @Id int = null;
	select top 1 @Id = T.ID from TB_ASSET T WHERE T.ASSET_TID = @Tid; -- CHECK EXIST TID

	if @Id is null or @Id=0 /* CRITERIA FOR INSERT NEW*/
	begin
		
		begin try
				
			-- DO INSERT
			print 'INSERTION AS NEW RECORD...'

			INSERT INTO TB_ASSET
			(
				ROOM_CODE,
				ASSET_EPC,
				ASSET_TID,
				ASSET_FID,
				ASSET_LABEL,
				ASSET_TYPE,
				ASSET_DESCRIPTION				
			) 
			VALUES 
			(
				@RoomCode,
				@Epc,
				@Tid,
				@Fid,
				@AssetLabel,
				@AssetType,
				@AssetDescription
			)
			
			set @RowCount = @@ROWCOUNT;
			
			-- RETURN
			IF @RowCount>0 -- INSERTION SUCCESS
			BEGIN
				print 'INSERTION SUCCESS.'
				set @MessageResult = 'Insertion a new asset success.';
				return 0;
			END
			ELSE -- NOTHING
			BEGIN
				print 'INSERTION NOTHING'
				set @MessageResult = 'There is no any save activity.';
				return -1;
			END
		end try
		begin catch
			set @RowCount = 0;
			set @MessageResult = ERROR_MESSAGE();
			return -2;
		end catch
		
	END
	else -- do update the asset recode by TID
	begin
		
		begin try

			print 'UPDATING...'
			
			update TB_ASSET
			set 
				ROOM_CODE = @RoomCode,
				ASSET_EPC = @Epc,
				ASSET_FID = @Fid,
				ASSET_LABEL = @AssetLabel,
				ASSET_TYPE = @AssetType,
				ASSET_DESCRIPTION = @AssetDescription
			where ASSET_TID=@Tid;

			set @RowCount=@@ROWCOUNT;

			-- RETURN
			IF @RowCount>0 -- UPDATED
			BEGIN
				PRINT 'UPDATING SUCCESS';
				set @MessageResult = 'Asset data updated successful.';
				return 0
			END
			ELSE -- NOTHING
			BEGIN
				PRINT 'Nothing updated';
				set @MessageResult = 'There is no any save activity.';
				return -1
			END

		end try
		begin catch
			set @RowCount = 0;
			set @MessageResult = ERROR_MESSAGE();
			return -2;
		end catch

	end

	-- safety
	return -99;

/* END */
END
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_SearchByFid]    Script Date: 13/1/2562 23:11:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[Sp_Asset_SearchByFid]
	-- Add the parameters for the stored procedure here
	@FID nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- fid
	IF @FID is NULL
	begin
		print 'Invalid TID! TID cannot be null.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end
	IF @FID = ''
	begin
		print 'Invalid TID! TID cannot be empty.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end

	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'TID = ' + + RTRIM(CAST(@FID AS nvarchar(50)))
	print 'SELECT and join data from TB_ASSET, TB_ROOM and TB_ASSET_TYPE'

	BEGIN TRY

		SELECT  T1.ID, T1.ASSET_TID , T1.ROOM_CODE, T1.ASSET_EPC, T1.ASSET_FID, T1.ASSET_LABEL, T1.ASSET_TYPE, T1.ASSET_DESCRIPTION,
		  T2.ROOM_TID, T2.ROOM_EPC, T2.ROOM_DESCRIPTION		from TB_ASSET T1
		LEFT JOIN TB_ROOM T2
		ON T1.ROOM_CODE=T2.ROOM_CODE
		WHERE T1.ASSET_FID=@FID;
						
		SET @RowCount = @@ROWCOUNT;
			
		print 'Done selection'
		IF @RowCount>0 -- data found.
		BEGIN
			SET @MessageResult = 'Asset found.';
			return 0
		END
		ELSE -- data not found!
		BEGIN
			SET @MessageResult = 'Asset not found!';
			return -1
		END

	END TRY
	BEGIN CATCH
		print 'QUERY ERROR'
		SET @RowCount = 0;
		SET @MessageResult = ERROR_MESSAGE();
		return -2
	END CATCH

	-- SAFETY
	return -99

-- END OF STORE PROCEDURE.
END
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_SearchByTid]    Script Date: 13/1/2562 23:11:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[Sp_Asset_SearchByTid]
	-- Add the parameters for the stored procedure here
	@TID nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- tid
	IF @TID is NULL
	begin
		print 'Invalid TID! TID cannot be null.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end
	-- empty
	IF @TID = ''
	begin
		print 'Invalid TID! TID cannot be empty.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end

	Declare @Id_room int = null;
	select top 1 @Id_room = T.ID from TB_ROOM T WHERE T.ROOM_TID = @Tid; -- CHECK EXIST TID
	if @Id_room is not null or @Id_room <> 0
	begin
				print 'TID is duplicate in ROOM.'
				set @RowCount=0;
				set @MessageResult = 'TID is duplicate in ROOM.';
				return -2;
	end
	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'TID = ' + + RTRIM(CAST(@TID AS nvarchar(50)))
	print 'SELECT and join data from TB_ASSET, TB_ROOM and TB_ASSET_TYPE'

	BEGIN TRY

		SELECT  T1.ID, T1.ASSET_TID , T1.ROOM_CODE, T1.ASSET_EPC, T1.ASSET_FID, T1.ASSET_LABEL, T1.ASSET_TYPE, T1.ASSET_DESCRIPTION,
		  T2.ROOM_TID, T2.ROOM_EPC, T2.ROOM_DESCRIPTION
		from TB_ASSET T1
		LEFT JOIN TB_ROOM T2
		ON T1.ROOM_CODE=T2.ROOM_CODE
		WHERE T1.ASSET_TID=@TID;
						
		SET @RowCount = @@ROWCOUNT;
			
		print 'Done selection'
		IF @RowCount>0 -- data found.
		BEGIN
			SET @MessageResult = 'Asset found.';
			return 0
		END
		ELSE -- data not found!
		BEGIN
			SET @MessageResult = 'Asset not found!';
			return -1
		END

	END TRY
	BEGIN CATCH
		print 'QUERY ERROR'
		SET @RowCount = 0;
		SET @MessageResult = ERROR_MESSAGE();
		return -2
	END CATCH

	-- SAFETY
	return -99

-- END OF STORE PROCEDURE.
END
GO
/****** Object:  StoredProcedure [dbo].[Sp_Room_Save]    Script Date: 13/1/2562 23:11:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[Sp_Room_Save] -- !!! สำคัญ ต้องเปลี่ยน Activity type
	@Epc nvarchar(50),	
	@Tid nvarchar(50),
	@RoomCode nvarchar(50),
	@RoomDescription nvarchar(1000),	
	@RowCount int output,
	@MessageResult nvarchar(100) output
AS
BEGIN

	-- ===================================================================================
	-- STATE-1: VALIDATION
	--             - CHECK NULL
	--             - CHECK EMPTY
	-- ===================================================================================
	
	-- TID
	IF @Tid is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end	
	IF @Tid=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end	
	-- FID
	IF @RoomCode is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid Room Code! Room Code cannot be null.';
		return -2;
	end	
	IF @RoomCode=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid Room Code! Room Code cannot be empty.';
		return -2;
	end	

	-- ===================================================================================
	-- STATE-2: SAVE BY INSERT OR UPDATE
	-- ===================================================================================	
	Declare @Id int = null;
	select top 1 @Id = R.ID from TB_ROOM R WHERE R.ROOM_CODE = @RoomCode; -- CHECK EXIST TID

	if @Id is null or @Id=0 /* CRITERIA FOR INSERT NEW*/
	begin
		
		begin try
				
			-- DO INSERT
			print 'INSERTION AS NEW RECORD...'

			INSERT INTO TB_ROOM
			(
				ROOM_EPC,
				ROOM_TID,
				ROOM_CODE,
				ROOM_DESCRIPTION
			) 
			VALUES 
			(
				@Epc,
				@Tid,
				@RoomCode,
				@RoomDescription
			)
			
			set @RowCount = @@ROWCOUNT;
			
			-- RETURN
			IF @RowCount>0 -- INSERTION SUCCESS
			BEGIN
				print 'INSERTION SUCCESS.'
				set @MessageResult = 'Insertion a new Room success.';
				return 0;
			END
			ELSE -- NOTHING
			BEGIN
				print 'INSERTION NOTHING'
				set @MessageResult = 'There is no any save activity.';
				return -1;
			END
		end try
		begin catch
			set @RowCount = 0;
			set @MessageResult = ERROR_MESSAGE();
			return -2;
		end catch
		
	END
	else -- do update the asset recode by TID
	begin
		
		begin try

			print 'UPDATING...'
			
			update TB_ROOM
			set 
				ROOM_EPC = @Epc,
				ROOM_TID = @Tid,
				ROOM_CODE = @RoomCode,
				ROOM_DESCRIPTION = @RoomDescription
			where ROOM_CODE=@RoomCode;

			set @RowCount=@@ROWCOUNT;

			-- RETURN
			IF @RowCount>0 -- UPDATED
			BEGIN
				PRINT 'UPDATING SUCCESS';
				set @MessageResult = 'Room data updated successful.';
				return 0
			END
			ELSE -- NOTHING
			BEGIN
				PRINT 'Nothing updated';
				set @MessageResult = 'There is no any save activity.';
				return -1
			END

		end try
		begin catch
			set @RowCount = 0;
			set @MessageResult = ERROR_MESSAGE();
			return -2;
		end catch

	end

	-- safety
	return -99;

/* END */
END
GO
/****** Object:  StoredProcedure [dbo].[Sp_Room_SearchByRoomCode]    Script Date: 13/1/2562 23:11:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[Sp_Room_SearchByRoomCode]
	-- Add the parameters for the stored procedure here
	@RoomCode nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- fid
	IF @RoomCode is NULL
	begin
		print 'Invalid Room Code! Room Code cannot be null.';
		-- THROW 50031, 'Invalid Room Code! Room Code can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid Room Code! Room Code cannot be null.';
		return -2;
	end
	IF @RoomCode = ''
	begin
		print 'Invalid Room Code! Room Code cannot be empty.';
		-- THROW 50031, 'Invalid Room Code! Room Code can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid Room Code! Room Code cannot be empty.';
		return -2;
	end

	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'Room Code = ' + + RTRIM(CAST(@RoomCode AS nvarchar(50)))
	print 'SELECT and join data from TB_ROOM'

	BEGIN TRY

		SELECT   T1.ID, T1.ROOM_CODE, T1.ROOM_TID, T1.ROOM_EPC, T1.ROOM_DESCRIPTION,
		 T2.ASSET_TID , T2.ASSET_EPC, T2.ASSET_FID, T2.ASSET_LABEL, T2.ASSET_TYPE, T2.ASSET_DESCRIPTION
		from  TB_ROOM T1
		LEFT JOIN TB_ASSET T2
		ON T1.ROOM_CODE = T2.ROOM_CODE
		WHERE T1.ROOM_CODE = @RoomCode;
						
		SET @RowCount = @@ROWCOUNT;
			
		print 'Done selection'
		IF @RowCount>0 -- data found.
		BEGIN
			SET @MessageResult = 'Room found.';
			return 0
		END
		ELSE -- data not found!
		BEGIN
			SET @MessageResult = 'Room not found!';
			return -1
		END

	END TRY
	BEGIN CATCH
		print 'QUERY ERROR'
		SET @RowCount = 0;
		SET @MessageResult = ERROR_MESSAGE();
		return -2
	END CATCH

	-- SAFETY
	return -99

-- END OF STORE PROCEDURE.
END
GO
/****** Object:  StoredProcedure [dbo].[Sp_Room_SearchByTID]    Script Date: 13/1/2562 23:11:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[Sp_Room_SearchByTID]
	-- Add the parameters for the stored procedure here
	@TID nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- fid
	IF @TID is NULL
	begin
		print 'Invalid Room TID! Room TID cannot be null.';
		-- THROW 50031, 'Invalid Room TID! Room TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid Room TID! Room TID cannot be null.';
		return -2;
	end
	IF @TID = ''
	begin
		print 'Invalid Room TID! Room TID cannot be empty.';
		-- THROW 50031, 'Invalid Room TID! Room TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid Room TID! Room TID cannot be empty.';
		return -2;
	end

	Declare @Id_asset int = null;
	select top 1 @Id_asset = T.ID from TB_ASSET T WHERE T.ASSET_TID = @Tid; -- CHECK EXIST TID
	if @Id_asset is not null or @Id_asset <> 0
	begin
				print 'TID is duplicate in ASSET.'
				set @RowCount=0;
				set @MessageResult = 'TID is duplicate in ASSET.';
				return -2;
	end
	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'Room TID = ' + + RTRIM(CAST(@TID AS nvarchar(50)))
	print 'SELECT and join data from TB_ROOM'

	BEGIN TRY

		SELECT   T1.ID, T1.ROOM_CODE, T1.ROOM_TID, T1.ROOM_EPC, T1.ROOM_DESCRIPTION,
		 T2.ASSET_TID , T2.ASSET_EPC, T2.ASSET_FID, T2.ASSET_LABEL, T2.ASSET_TYPE, T2.ASSET_DESCRIPTION		  
		from  TB_ROOM T1
		LEFT JOIN TB_ASSET T2
		ON T1.ROOM_CODE = T2.ROOM_CODE
		WHERE T1.ROOM_TID = @TID;
						
		SET @RowCount = @@ROWCOUNT;
			
		print 'Done selection'
		IF @RowCount>0 -- data found.
		BEGIN
			SET @MessageResult = 'Room found.';
			return 0
		END
		ELSE -- data not found!
		BEGIN
			SET @MessageResult = 'Room not found!';
			return -1
		END

	END TRY
	BEGIN CATCH
		print 'QUERY ERROR'
		SET @RowCount = 0;
		SET @MessageResult = ERROR_MESSAGE();
		return -2
	END CATCH

	-- SAFETY
	return -99

-- END OF STORE PROCEDURE.
END
GO
USE [master]
GO
ALTER DATABASE [DB_FIXED_ASSET] SET  READ_WRITE 
GO
