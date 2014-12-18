<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Venster2
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Venster2))
        Me.rtb_over = New System.Windows.Forms.RichTextBox()
        Me.pb_robot = New System.Windows.Forms.PictureBox()
        CType(Me.pb_robot, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'rtb_over
        '
        Me.rtb_over.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.rtb_over.Enabled = False
        Me.rtb_over.Location = New System.Drawing.Point(12, 12)
        Me.rtb_over.Name = "rtb_over"
        Me.rtb_over.ReadOnly = True
        Me.rtb_over.Size = New System.Drawing.Size(181, 172)
        Me.rtb_over.TabIndex = 0
        Me.rtb_over.Text = ""
        '
        'pb_robot
        '
        Me.pb_robot.Image = CType(resources.GetObject("pb_robot.Image"), System.Drawing.Image)
        Me.pb_robot.Location = New System.Drawing.Point(174, 12)
        Me.pb_robot.Name = "pb_robot"
        Me.pb_robot.Size = New System.Drawing.Size(195, 172)
        Me.pb_robot.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.pb_robot.TabIndex = 1
        Me.pb_robot.TabStop = False
        '
        'Venster2
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(381, 196)
        Me.Controls.Add(Me.pb_robot)
        Me.Controls.Add(Me.rtb_over)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "Venster2"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Over"
        CType(Me.pb_robot, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents rtb_over As System.Windows.Forms.RichTextBox
    Friend WithEvents pb_robot As System.Windows.Forms.PictureBox
End Class
