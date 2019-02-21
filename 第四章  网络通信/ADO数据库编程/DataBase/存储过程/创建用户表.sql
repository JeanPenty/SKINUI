USE [master]
GO

/****** Object:  Table [dbo].[UserData]    Script Date: 12/18/2013 17:21:47 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[UserData](
	[UserID] [int] IDENTITY(1,1) NOT NULL,
	[NickName] [nvarchar](31) NOT NULL,
	[LogonPass] [nvarchar](31) NOT NULL,
	[Experience] [int] NOT NULL,
	[Gender] [tinyint] NOT NULL,
	[IsAndroid] [tinyint] NOT NULL,
 CONSTRAINT [PK_UserData] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[UserData] ADD  CONSTRAINT [DF_UserData_NickName]  DEFAULT ('') FOR [NickName]
GO


